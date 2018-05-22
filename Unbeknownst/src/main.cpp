#include "StateMachine\stateMachine.hpp"
#include "StateMachine\States\titleScreen.hpp"

int main() {

	StateMachine machine;
	machine.PushState(TitleScreenState::Instance());

	while (machine.Running()) {
		machine.HandleEvents();
		machine.Update();
		machine.Render();
	}

	machine.CleanUp();

}