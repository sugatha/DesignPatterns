#include "Header.h"



class Journal
{
	string title_;
	vector<string> entries_;
public:
	void set_title(string pTitle) { title_ = pTitle; }
	string get_title() { return title_; }

	void set_entries(vector<string> pEntries) { entries_ = pEntries; }
	vector<string> get_entries() const { return entries_; }

	Journal() {}
	Journal(const Journal& jrnl) { this->title_ = jrnl.title_; }

	explicit Journal(const string & pTitle) : title_{ pTitle } {}

	__declspec(property(get = get_tile, put = set_title)) string title;
	__declspec(property(get = get_entries, put = set_entries)) vector<string> entries;

	void add(const string& entry)
	{
		static int count = 1;
		entries_.push_back(boost::lexical_cast<string>(count++) + ": " + entry);
	}

	/* This shouldnt be here, its not the responsibility of the journal to persist */
	void save(const string& filename)
	{
		 ofstream ofs(filename);
		 for (auto& s : entries_)
		 ofs << s << endl;

		 ofs.close();
	}
};

class PersistenceManager
{
public:
	static void save(const Journal & j, const string & filename)
	{
		ofstream ofs(filename);
		for (auto& s : j.entries)
			ofs << s << endl;
	}
};