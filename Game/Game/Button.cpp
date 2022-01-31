#include "includeAll.h"
#include "Button.h"

Button::Button(float x, float y, float width, float hieght,
	Font* font, string text, unsigned char_size,
	Color text_idleColor, Color text_hoverColor, Color txet_activeColor,
	Color idleColor, Color hoverColor, Color activeColor)
{
	this->buttonState = BTN_IDLE;

	this->shape.setPosition(Vector2f(x, y));
	this->shape.setSize(Vector2f(width, hieght));
	this->shape.setFillColor(idleColor);

	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(text_idleColor);
	this->text.setCharacterSize(char_size);
	this->text.setOrigin(
		this->text.getLocalBounds().left + this->text.getLocalBounds().width / 2.f, 
		this->text.getLocalBounds().top + this->text.getLocalBounds().height / 2.f
	);
	this->text.setPosition(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f),
		this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f)
	);

	this->text_idleColor = text_idleColor;
	this->text_hoverColor = text_hoverColor;
	this->text_activeColor = text_activeColor;

	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;

}

Button::~Button()
{

}

const bool Button::isPressed() const
{
	if (this->buttonState == BTN_ACTIVE)
		return true;

	return false;
}

void Button::update(const Vector2f& mousePos)
{
	this->buttonState = BTN_IDLE;

	if (this->shape.getGlobalBounds().contains(mousePos))
	{
		this->buttonState = BTN_HOVER;

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			this->buttonState = BTN_ACTIVE;
		}
	}

	switch (this->buttonState)
	{
	case BTN_IDLE:
		this->shape.setFillColor(this->idleColor);
		this->text.setFillColor(this->text_idleColor);
		break;

	case BTN_HOVER:
		this->shape.setFillColor(this->hoverColor);
		this->text.setFillColor(this->text_hoverColor);
		break;

	case BTN_ACTIVE:
		this->shape.setFillColor(this->activeColor);
		this->text.setFillColor(this->text_activeColor);
		break;

	default:
		this->shape.setFillColor(Color::Red);
		this->text.setFillColor(Color::Blue);
		break;
	}
}

void Button::render(RenderTarget& target)
{
	target.draw(this->shape);
	target.draw(this->text);
}
