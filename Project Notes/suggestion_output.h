#ifndef SUGG
#define SUGG

class suggestion_output
{
protected:
	Font font;
	Text text;
	std::string m_adress;
	std::string m_text_sugg;
	int m_size;
	float m_x;
	float m_y;
	int color1;
	int color2;
	int color3;
public:
	suggestion_output(std::string adress = "fonts\\FORTE.ttf", std::string text_sug = "Hello,dear user", int size = 24, float x = 200.0f, float y = 200.0f,
	int one=0,int two=0,int three=0 )
		:m_adress(adress), m_text_sugg(text_sug), m_size(size), m_x(x), m_y(y),color1(one),color2(two),color3(three)
	{
		font.loadFromFile(m_adress);
		text.setFont(font);
		text.setCharacterSize(m_size);
		text.setFillColor(Color::Black);
		text.setString(m_text_sugg);
		text.setPosition(Vector2f(m_x, m_y));
		text.setFillColor(Color(color1, color2, color3));
	}
	//since all class member variables have protected access, we create an access function for external objects
	Text access_text()
	{
		return text;
	}
};
#endif
