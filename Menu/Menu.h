#ifndef MENU_H
#define MENU_H


#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>


#include "Button.h"

using namespace sf;
/* �����-���� ����� ������� ����
* �������������:
* 1) ������� ������, ������� � ����������� ������� ����
* 2) ����� main loop ������� ������� exec()
* 3) Profit!
*/
class StartMenu
{
public:
	//�������� ������ �� ���� � ������������ ��������� ���������� �� ���� ������������� � ������� ������
	StartMenu(RenderWindow &window);
	~StartMenu();
	void exec(); // ������ ����!
private:
	// ����� ������ ����� ��������?
	enum Button_current{
		start,
		setting,
		autors,
		quit
	};
	void render(); // ���������� � exec(), ������ ���������
	RenderWindow &_window; // ������� ����
	Button _start; // ����� ��������
	Button _settings; // ���������
	Button _autors; // ����� ( � ���)
	Button _quit; // ������ ������
	RectangleShape _back; // ������
	RectangleShape _menu; // ������ ����� �������
	Event _event; // ������� ���� ����, ������ �� ������������ �������
	Button_current _focus_button; // ����� ������ ������ ��������?
};

#endif // STARTMENU_H
