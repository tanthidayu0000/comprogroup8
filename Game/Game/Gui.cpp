#include "includeAll.h"
#include "Gui.h"

const float gui::p2pX(const float perc, const VideoMode& vm)
{
	return floor(static_cast<float>(vm.width) * (perc / 100.f));
}

const float gui::p2pY(const float perc, const VideoMode& vm)
{
	return floor(static_cast<float>(vm.height) * (perc / 100.f));
}

const unsigned gui::calcCharSize(const VideoMode& vm, const unsigned modifier)
{

	return static_cast<unsigned>((vm.width + vm.height) / modifier);
}

gui::Button::Button(float x, float y, float width, float hieght,
	Font* font, string text, unsigned char_size,
	Color text_idleColor, Color text_hoverColor, Color txet_activeColor,
	Color idleColor, Color hoverColor, Color activeColor,
	Color outline_idleColor, Color outline_hoverColor, Color outline_activeColor,
	short unsigned id)
{
	this->buttonState = BTN_IDLE;
	this->id = id;

	this->shape.setPosition(Vector2f(x, y));
	this->shape.setSize(Vector2f(width, hieght));
	this->shape.setFillColor(idleColor);
	this->shape.setOutlineThickness(1.f);
	this->shape.setOutlineColor(outline_idleColor);

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
	this->text_activeColor = txet_activeColor;

	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;

	this->outlineIdleColor = outline_idleColor;
	this->outlineHoverColor = outline_hoverColor;
	this->outlineActiveColor = outline_activeColor;
}

gui::Button::~Button()
{

}

const bool gui::Button::isPressed() const
{
	if (this->buttonState == BTN_ACTIVE)
		return true;

	return false;
}

const string gui::Button::getText() const
{
	return this->text.getString();
}

const short unsigned& gui::Button::getId() const
{
	return this->id;
}

void gui::Button::setText(const string text)
{
	this->text.setString(text);
}

void gui::Button::setId(const short unsigned id)
{
	this->id = id;
}

void gui::Button::update(const Vector2f& mousePos)
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
		this->shape.setOutlineColor(this->outlineIdleColor);
		break;

	case BTN_HOVER:
		this->shape.setFillColor(this->hoverColor);
		this->text.setFillColor(this->text_hoverColor);
		this->shape.setOutlineColor(this->outlineHoverColor);
		break;

	case BTN_ACTIVE:
		this->shape.setFillColor(this->activeColor);
		this->text.setFillColor(this->text_activeColor);
		this->shape.setOutlineColor(this->outlineActiveColor);
		break;

	default:
		this->shape.setFillColor(Color::Red);
		this->text.setFillColor(Color::Blue);
		this->shape.setOutlineColor(Color::White);
		break;
	}
}

void gui::Button::render(RenderTarget& target)
{
	target.draw(this->shape);
	target.draw(this->text);
}

gui::DropDownList::DropDownList(float x, float y, float width, float height, 
	Font& font, string list[], 
	unsigned nrOfElement, unsigned default_index)
	:font(font), showList(false), keyTimeMax(2.f), keyTime(0.f)
{
	this->activeElement = new gui::Button(
		x, y, width, height,
		&this->font, list[default_index], 20,
		Color(255, 255, 255, 150), Color(255, 255, 255, 200), Color(20, 20, 20, 50),
		Color(70, 70, 70, 255), Color(150, 150, 150, 255), Color(20, 20, 20, 255),
		Color(255, 255, 255, 200), Color(255, 255, 255, 255), Color(20, 20, 20, 50)
	);

	for (size_t i = 0; i < nrOfElement; i++)
	{
		this->list.push_back(
			new gui::Button(
				x, y + ((i+1) * height), width, height,
				&this->font, list[i], 20,
				Color(255, 255, 255, 150), Color(255, 255, 255, 255), Color(20, 20, 20, 50),
				Color(70, 70, 70, 255), Color(150, 150, 150, 255), Color(20, 20, 20, 255),
				Color(255, 255, 255, 0), Color(255, 255, 255, 0), Color(20, 20, 20, 0),
				i
			)
		);
	}

}

gui::DropDownList::~DropDownList()
{
	delete this->activeElement;
	for (size_t i = 0; i < list.size(); i++)
	{
		delete this->list[i];
	}
}

const string gui::DropDownList::getActiveElementText() const
{
	return this->activeElement->getText();
}

const unsigned short& gui::DropDownList::getActiveElementId() const
{
	return this->activeElement->getId();
}

const bool gui::DropDownList::getKeyTime()
{
	if (this->keyTime >= this->keyTimeMax)
	{
		this->keyTime = 0.f;
		return true;
	}

	return false;
}

void gui::DropDownList::updateKeyTime(const float& dt)
{
	if (this->keyTime < this->keyTimeMax)
		this->keyTime += 10.f * dt;
}

void gui::DropDownList::update(const Vector2f& mousePos, const float& dt)
{
	this->updateKeyTime(dt);
	this->activeElement->update(mousePos);

	if (this->activeElement->isPressed() && this->getKeyTime())
	{
		if (this->showList)
			this->showList = false;
		else
			this->showList = true;
	}

	if (this->showList)
	{
		for (auto &i : this->list)
		{
			i->update(mousePos);

			if (i->isPressed() && this->getKeyTime())
			{
				this->showList = false;
				this->activeElement->setText(i->getText());
				this->activeElement->setId(i->getId());
			}
		}
	}
}

void gui::DropDownList::render(RenderTarget& target)
{
	this->activeElement->render(target);

	if (this->showList)
	{
		for (auto& i : this->list)
		{
			i->render(target);
		}
	}
}
