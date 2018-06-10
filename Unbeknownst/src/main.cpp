#include "StateMachine\stateMachine.hpp"
#include "StateMachine\States\titleScreen.hpp"

static const float SECONDS_PER_FPS_CHECK{ 1.0f };
static const float SECONDS_PER_UPDATE_CALL{ 0.2f };

int main() {

	StateMachine machine;
	machine.PushState(TitleScreenState::Instance());

	sf::Clock clock;
	sf::Time elapsedTime;

	float delayTimer{ 0.0f };
	float frameTimer{ 0.0f };

	unsigned int frameCounter{ 0 };

	while (machine.Running()) {

		elapsedTime = clock.restart();

		delayTimer += elapsedTime.asSeconds();
		frameTimer += elapsedTime.asSeconds();

		if (frameTimer >= SECONDS_PER_FPS_CHECK) {
			machine.UpdateFPS(frameCounter);
			frameTimer = 0.0f;
			frameCounter = 0;
		}

		machine.HandleEvents();

		if (!machine.Running()) {
			break;
		}

		while (delayTimer >= SECONDS_PER_UPDATE_CALL) {
			machine.Update();
			delayTimer -= SECONDS_PER_UPDATE_CALL;
		}
		
		machine.Render();
		frameCounter++;
	}

	machine.CleanUp();

}