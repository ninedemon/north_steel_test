#ifndef PAGE
#define PAGE

class page_number:public suggestion_output
{
private:
	//creating a variable that will store the current page number
	int number_page;
public:
	page_number(int number=1,std::string adress = "fonts\\BRUSHSCI.ttf", std::string text1 = "page number:", int size = 40, float x = 480.0f, float y = 650.0f)
		:suggestion_output(adress,text1,size,x,y),number_page(number)
	{
		std::ostringstream number_list;
		number_list << number_page;
		text.setString(text1 + number_list.str());
		text.setFillColor(Color::Blue);
	}
	
	int access_number_page()
	{
		return number_page;
	}
	
	page_number& operator=(const page_number& one)
	{
		number_page = one.number_page;
		std::ostringstream number_list;
		number_list << number_page;
		text.setString("page number:" + number_list.str());
		return *this;
	}
	
};
#endif
