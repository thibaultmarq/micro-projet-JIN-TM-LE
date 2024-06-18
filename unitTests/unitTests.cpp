#include <gtest/gtest.h>
#include "StaticSurface.h"
#include "MovingSurface.h"

class SurfaceTest : public ::testing::Test {
protected:
    void SetUp() override {
        world = new b2World(b2Vec2(0.0f, 0.0f));
    }

    void TearDown() override {
        delete world;
    }

    b2World* world;
};


TEST_F(SurfaceTest, Construction) {
    
    StaticSurface surface(0.0f, 0.0f, 10.0f, 5.0f, SurfaceType::TOUCHABLE, *world);

    EXPECT_EQ(surface.getType(), SurfaceType::TOUCHABLE);

}

TEST_F(SurfaceTest, SwimmableSurface) {
    StaticSurface surface(0.0f, 0.0f, 10.0f, 5.0f, SurfaceType::SWIMMABLE, *world);

    EXPECT_EQ(surface.getType(), SurfaceType::SWIMMABLE);
    EXPECT_EQ(surface.getTarget().getFillColor(), sf::Color::White);
}

TEST_F(SurfaceTest, RenderPosition) {
    StaticSurface surface(0.0f, 0.0f, 10.0f, 5.0f, SurfaceType::TOUCHABLE, *world);

    sf::RenderTexture renderTexture;
    renderTexture.create(800, 600);
    surface.render(renderTexture);

    EXPECT_EQ(surface.getTarget().getPosition().x, 0);
    EXPECT_EQ(surface.getTarget().getPosition().y, 0);
    StaticSurface swimmableSurface(0.0f, 0.0f, 10.0f, 5.0f, SurfaceType::SWIMMABLE, *world);
    swimmableSurface.render(renderTexture);
    EXPECT_EQ(swimmableSurface.getTarget().getPosition().x, -0.5);
    EXPECT_EQ(swimmableSurface.getTarget().getPosition().y, -0.5);

}

