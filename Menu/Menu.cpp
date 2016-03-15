#include "Menu.h"


StartMenu::StartMenu(RenderWindow &window) :
_window(window),
_start(L"START", window.getView().getSize().x / 2.7, window.getView().getSize().y / 3),
_settings(L"Settings", _start.getGlobalBounds().left, _start.getGlobalBounds().top + _start.getGlobalBounds().height),
_autors(L"Authors", _start.getGlobalBounds().left, _settings.getGlobalBounds().top + _settings.getGlobalBounds().height),
_quit(L"Quit", _start.getGlobalBounds().left, _autors.getGlobalBounds().top + _autors.getGlobalBounds().height)

{
	_focus_button = start;
}
void StartMenu::exec(){
	while (true){
		while (_window.pollEvent(_event)){
			switch (_event.type) {
			case Event::Closed:
				_window.close();
				return;
				break;
			case Event::KeyPressed:
				if (Keyboard::isKeyPressed(Keyboard::Down))
					_focus_button = Button_current((_focus_button + 1) % 4);// % n , ��� n - ���������� ������
				if (Keyboard::isKeyPressed(Keyboard::Up))
					_focus_button = Button_current((_focus_button == 0) ? 3 : _focus_button - 1);
				if (Keyboard::isKeyPressed(Keyboard::Return)) // ���� ������ ���������� �����
					switch (_focus_button){ // � ����������� �� ����, ����� ����� ��������
					case start: // ������ ������
						return; // ��������� ������, ���� ����������
						break;
					case setting: // ���������
						//start_settings();
						break;
					case autors:
						//Show_autors();
						break;
					case quit:
						_window.close();
						return;
				}

			}

		} // pollEvent()

		_window.clear();
		render();
		_window.display();
	} // while(true)
}

void StartMenu::render(){
	// ������� ������ ���������
	_start.setFocus(false);
	_settings.setFocus(false);
	_autors.setFocus(false);
	_quit.setFocus(false);

	// ������ �����
	switch (_focus_button) {
	case start:
		_start.setFocus();
		break;
	case setting:
		_settings.setFocus();
		break;
	case autors:
		_autors.setFocus();
		break;
	case quit:
		_quit.setFocus();
		break;
	}
	_window.draw(_back);
	_window.draw(_menu);
	_start.render(_window);
	_settings.render(_window);
	_autors.render(_window);
	_quit.render(_window);
}

StartMenu::~StartMenu()
{

}

