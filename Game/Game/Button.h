#ifndef BUTTON_H
#define BUTTON_H

enum button_states { BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE };

class Button
{
private:
	short unsigned buttonState;

	RectangleShape shape;
	Font* font;
	Text text;

	Color idleColor;
	Color hoverColor;
	Color activeColor;

public:
	Button(float x, float y, float width, float hieght,
		Font* font, string text,
		Color idleColor, Color hoverColor, Color activeColor);
	virtual ~Button();

	const bool isPressed() const;

	void update(Vector2f mousePos);
	void render(RenderTarget* target);
};

#endif