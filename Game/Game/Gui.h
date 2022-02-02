#ifndef GUI_H
#define GUI_H

enum button_states { BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE };

namespace gui
{
	class Button
	{
	private:
		short unsigned buttonState;
		short unsigned id;

		RectangleShape shape;
		Font* font;
		Text text;

		Color text_idleColor;
		Color text_hoverColor;
		Color text_activeColor;

		Color idleColor;
		Color hoverColor;
		Color activeColor;

		Color outlineIdleColor;
		Color outlineHoverColor;
		Color outlineActiveColor;

	public:
		Button(float x, float y, float width, float hieght,
			Font* font, string text, unsigned char_size,
			Color text_idleColor, Color text_hoverColor, Color txet_activeColor,
			Color idleColor, Color hoverColor, Color activeColor,
			Color outline_idleColor = Color::Transparent, Color outline_hoverColor = Color::Transparent, Color outline_activeColor = Color::Transparent,
			short unsigned id = 0);
		virtual ~Button();

		const bool isPressed() const;
		const string getText() const;
		const short unsigned& getId() const;

		void setText(const string text);
		void setId(const short unsigned id);

		void update(const Vector2f& mousePos);
		void render(RenderTarget& target);
	};

	class DropDownList
	{
	private:
		float keyTime;
		float keyTimeMax;

		Font font;
		gui::Button* activeElement;
		vector<gui::Button*> list;
		bool showList;

	public:
		DropDownList(float x, float y, float width, float height, Font& font, string list[], unsigned nrOfElement, unsigned default_index = 0);
		~DropDownList();

		const bool getKeyTime();
		void updateKeyTime(const float& dt);
		void update(const Vector2f& mousePos, const float& dt);
		void render(RenderTarget& target);
	};
}

#endif