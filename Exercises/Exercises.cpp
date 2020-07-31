// Exercises.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "propertry.h"
#include "SingleResponsibility.h"
#include "OpenClose.h"
#include "LiskovSubstitution.h"
#include "Unique_ptr.h"
#include "Shared_Ptr.h"
#include "DependencyInversion.h"
#include "ObjectReturn.h"

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

	/* Unique_ptr */
	{
		auto p = make_unique<UniqueDerived>(); // p is a unique_ptr that owns a Derived
		auto q = pass_through(move(p));
		assert(!p);	// now p owns nothing and holds a null pointer
		q->bar();   // and q owns the Derived object
	}

	/* Shared_ptr */
	{
		shared_ptr<Base> p = make_shared<Derived>();

		cout	<< "Created a shared Derived (as a pointer to Base)\n"
					<< "  p.get() = " << p.get()
					<< ", p.use_count() = " << p.use_count() << '\n';

		thread	t1(thr, p), 
				t2(thr, p), 
				t3(thr, p);

		p.reset(); // release ownership from main
		
		cout << "Shared ownership between 3 threads and released\n"
			<< "ownership from main:\n"
			<< "  p.get() = " << p.get()
			<< ", p.use_count() = " << p.use_count() << '\n';
		
		t1.join();
		t2.join(); 
		t3.join();
		
		cout << "All threads completed, the last one deleted Derived\n";
	}

	/*Dependency Inversion */
	{
		auto injector = di::make_injector(di::bind<ILogger>().to<ConsoleLogger>());
	}

	/*Returning objects */	
	Foo f = make_foo(2);

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
