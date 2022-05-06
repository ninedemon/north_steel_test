#include <SFML/Graphics.hpp>
using namespace sf;
#include "background.h"
#include "suggestion_output.h"
#include "block_of_notes.h"
#include "page_number.h"
#include <fstream>
#include <cassert>



int main()
{
	//creating an application window
	RenderWindow window(VideoMode(1100, 900), L"Заметки!", Style::Default);
	//creating a block of notes
	block_of_notes one;
	//creating an object that stores information about the page number
	page_number list;
	//output the saved information
	std::ifstream input_save;
	input_save.open("save_notes.txt");
	//check if the file has been opened
	assert(input_save.is_open() && "File save_notes.txt is not open");
	int page_text = 0;
	//output the saved information to a string array
	while (!input_save.eof())
	{
		std::string piece = "";
		std::getline(input_save, piece);
		if (piece == "massive")
			continue;
		if (piece == "endmassive")
		{
			page_text++;
			continue;
		}
		if (piece == "\n")
			continue;
		else
		{
			one.text_information.resize(page_text + 1);
			one[page_text] += piece;
			if (!(one[page_text] == ""))
				one[page_text] += '\n';
			
		}
	}
	input_save.close();
	//initialize the line with the user's greeting if the saved data is not loaded into it
	if (one[list.access_number_page() - 1] == "")
		one[list.access_number_page() - 1] = "Hello,dear user";

	int schet = 1;
	// The main application loop. Executed while the window is open
	while (window.isOpen())
	{

		//creating an orange background
		window.clear(Color(255, 130, 4));
		//forming a picture of the note
		background sheet("image\\page.png", 0.9f, 0.75f, 50.0f);
		window.draw(sheet.access_sprite());
		//output information about the number of notes
		window.draw(one.access_text());
		//output information about the numbering of the sheet
		window.draw(list.access_text());
		//creating a button to switch notes back
		background button1("image\\button.png", 0.2f, 0.2f, 850.0f, 650.0f);
		window.draw(button1.access_sprite());
		//creating a second button to switch notes forward
		background button2("image\\button.png", 0.2f, 0.2f, 250.0f, 770.0f, 180.0f);
		window.draw(button2.access_sprite());
		//creating a text deletion button on a specific page
		background button_delete("image\\button_delete.png", 0.18f, 0.18f, 300.0f, 665.0f);
		window.draw(button_delete.access_sprite());
		//creating a button to delete information on all sheets and delete all sheets
		background button_delete_save("image\\delete_all.png", 0.4f, 0.2f, 720.0f, 75.0f);
		suggestion_output on_button_delete_save("fonts\\BRUSHSCI.ttf", "Delete all", 40, 745.0f, 75.0f, 255, 255, 255);
		window.draw(button_delete_save.access_sprite());
		window.draw(on_button_delete_save.access_text());
		//Output a welcome message on the first page of the not
		if ((list.access_number_page() == 1) && (one[list.access_number_page() - 1] == ""))
		{
			suggestion_output new_text("fonts\\FORTE.ttf", one[0], 32, 150.0f, 200.0f);
			window.draw(new_text.access_text());
		}
		//creating a vector storing the mouse position inside the window
		Vector2i mousepozition = Mouse::getPosition(window);
		//if the user clicked on the left mouse button
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			//if the mouse cursor is in the area of the button that scrolls notes forward
			if (button1.access_sprite().getGlobalBounds().contains(static_cast<float>(mousepozition.x), static_cast<float>(mousepozition.y)))
			{
				schet += 1;
				//if the user wants to scroll to a page that is not yet in the array
				if (static_cast<int>(one.text_information.size()) < schet)
					one.text_information.resize(schet);
				list = page_number(schet);
			}
			//if the mouse cursor is in the area of the button scrolling notes back
			if (button2.access_sprite().getGlobalBounds().contains(static_cast<float>(mousepozition.x), static_cast<float>(mousepozition.y)))
				if (!(list.access_number_page() == 1))
				{
					schet -= 1;
					list = page_number(schet);
				}

			//if the mouse cursor is in the delete button area
			if (button_delete.access_sprite().getGlobalBounds().contains(static_cast<float>(mousepozition.x), static_cast<float>(mousepozition.y)))
			{
				one[list.access_number_page() - 1].resize(0);
			}
			//if the mouse cursor was in the area of the delete all button
			if (button_delete_save.access_sprite().getGlobalBounds().contains(static_cast<float>(mousepozition.x), static_cast<float>(mousepozition.y)))
			{
				int number_list = 0;
				while (static_cast<int>(one.text_information.size()) > number_list)
				{
					//reset the information on all elements of the array
					one[number_list] = "";
					number_list++;

				}
				// after zeroing all elements of the array, we change the size
				one.text_information.resize(1);
			}
		}

		// Processing the queue of events in the loop
		Event event;
		while (window.pollEvent(event))
		{
			// The user clicked on the "x" and wants to close the window
			if (event.type == Event::Closed)
			{
				//save the data of each page of the note
				std::ofstream save;
				save.open("save_notes.txt");
				assert(save.is_open() && "File save_notes.txt is not open");
				int text_page = 0;
				while (text_page < static_cast<int>(one.text_information.size()))
				{
					
					if (!(one[text_page]=="") && !(one[text_page]=="Hello,dear user"))
					{
						save << "massive" << std::endl;
						save << one[text_page];
						save << '\n';
						save << "endmassive";
						save << '\n';
					}
					text_page++;
				}
				save.close();
				// closing the program
				window.close();
			}
			//if the user pressed the keyboard button
			if (event.type == Event::TextEntered)
			{
				if (event.text.unicode < 128 && !(event.text.unicode == 8))
				{
					//if the array element contains information about the user's greeting
					if (one[list.access_number_page() - 1] == "Hello,dear user")
						// completely clear the array element
						while (!(one[list.access_number_page() - 1].size() == 0))
						{
							one[list.access_number_page() - 1].pop_back();
						}
					//loading information into an array element character-by-character
					one[list.access_number_page() - 1] += static_cast<char>(event.text.unicode);

				}
				//if the user clicked the backspace button and the row of the array element is not zero
				if (event.text.unicode == 8 && (!(one[list.access_number_page() - 1].size() == 0)))
					// delete the information from the array
					one[list.access_number_page() - 1].pop_back();
				if (event.text.unicode == 13)
					one[list.access_number_page() - 1].push_back('\n');
			}

		}
		//forming text for display
		suggestion_output main_text("fonts\\FORTE.ttf", one[list.access_number_page() - 1], 32, 150.0f, 200.0f);
		//forming a text output restriction along the OX axis
		if ((1.5 * (main_text.access_text().getGlobalBounds().width) > (sheet.access_sprite().getGlobalBounds().width)))
		{
			one[list.access_number_page() - 1].pop_back();
			one[list.access_number_page() - 1].push_back('\n');
		}
		//forming a text output restriction along the OY axis
		if ((2.5 * (main_text.access_text().getGlobalBounds().height)) > (sheet.access_sprite().getGlobalBounds().height))
			one[list.access_number_page() - 1].pop_back();
		//output the text to the buffer
		window.draw(main_text.access_text());
		//output everything that is in the buffer to the display
		window.display();
	}

	return 0;
}