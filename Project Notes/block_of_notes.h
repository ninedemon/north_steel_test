#ifndef BLOCK
#define BLOCK
#include <vector>
#include <sstream>
//we inherit the suggestion class so as not to create the same variables in classes
class block_of_notes:public suggestion_output
{
public:
	//creating an array storing text information of all pages of notes
	std::vector <std::string> text_information;

	block_of_notes(std::string adress="fonts\\BRUSHSCI.ttf",std::string text1="number of sheets:",int size=40,float x=460.0f,float y=700.0f)
		:suggestion_output(adress,text1,size,x,y)
	{
		text_information.resize(1);
		int quanity = static_cast<int>(text_information.size());
		std::ostringstream kolvo;
		kolvo << quanity;
		text.setString(text1 + kolvo.str());
		text.setFillColor(Color::Red);
	}
	
	std::string& operator[](const int index)
	{

		return text_information[index];
	}
	//since all class member variables have private access, we create an access function for external objects
	Text access_text()
	{
		int quanity = static_cast<int>(text_information.size());
		std::ostringstream kolvo;
		kolvo << quanity;
		text.setString("number of sheets:"+ kolvo.str());
		text.setFillColor(Color::Red);
		return text;
	}


};
#endif
