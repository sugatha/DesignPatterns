// Exercises.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "propertry.h"
#include "SingleResponsibility.h"
#include "OpenClose.h"
#include "LiskovSubstitution.h"

/*Forward declarations */
void process(Rectangle& r);

int main()
{
	Person perObj;
	perObj.age = 13;
	perObj.name = "mimmi";
	cout << perObj.name <<" is " << perObj.age << "yrs old."<<endl;	


	/* Single responsibility */
	{
			Journal jrnlObj("Monday");
			Journal jrnlObj1;
			jrnlObj1.title = "Tuesday";

			Journal jrnlObj2 = jrnlObj1;
			jrnlObj.add("He Hell-Oed me");

			/* Shouldn't be doing this here, as its logically not a part of journal */
			jrnlObj.save("c:\\temp\\sample.pig");

			/*BUT should be handled this way :)*/
			PersistenceManager pm;
			pm.save(jrnlObj, "c:\\temp\\sample.piggy");

	}

	/* Open and Close principle */
	{
			Product apple{ "Apple", Color::Green, Size::Small };
			Product tree{ "Tree", Color::Green, Size::Large };
			Product house{ "House", Color::Blue, Size::Large };
			vector<Product*> all{ &apple, &tree, &house };

			/* The Wrong way to filter */ 
			// {
				ProductFilter pf;
				auto result_green = pf.by_color(all, Color::Green);
				for (auto& p : result_green)
					cout << p->name << " is green" << endl;

				auto result_large = pf.by_color(all, Size::Large);
				for (auto& p : result_large)
					cout << p->name << " is large" << endl;
			// }

			/* The Right way to filter */
			// {
				BetterFilter bf;			
				ColorSpecification green(Color::Green);

				auto green_things = bf.filter(all, green);
				for (auto& x : green_things)
					cout << x->name << " is green" << endl;

				SizeSpecification large(Size::Large);

				auto large_things = bf.filter(all, large);
				for (auto& x : large_things)
					cout << x->name << " is large" << endl;

				/* Use the above created green and large */
				
				MultipleSpecification<Product> green_and_large{ large, green };
				auto big_green_things = bf.filter(all, green_and_large);
				for (auto& x : big_green_things)
					cout << x->name << " is large and green" << endl;

				

			// }
	 }

	/* Liskov Substitition principle */
	{
		Rectangle rect(3,4);
		process(rect);

		/* Oops! fails for a square */
		Square sq(3);
		process(sq);
	}

}

void process(Rectangle& r)
{
	int h = r.get_height();
	int w = r.get_width();
	/* increase the height of the rectangle by 200% */
	r.set_height(h * 2);
	cout	<< "expected area after increasing the height by 200% = " << (w* h * 2)	
			<< " h =" << r.get_height()
			<< " w = "<<r.get_width() 
			<< ", got " << r.area() << endl;
}
