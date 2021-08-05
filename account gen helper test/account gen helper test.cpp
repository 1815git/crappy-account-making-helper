#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS // for stopping error when getting time
#endif

#include <iostream>

#include <random>

#include <Windows.h> // for toClipboard function and others

#include <fstream> // for saving to files 

#include <chrono> // for getting time in ms

#include <ctime> // for getting date and time for header
#include <iomanip>
#include <sstream>

// short word list if you want to add a word increase the array size to match it
const std::string ShortWordList[82] =
{
    "bad",
    "easy",
    "lol",
    "LOL",
    "Hurt",
    "dude",
    "joe",
    "hate",
    "kill",
    "duo",
    "fire",
    "book",
    "power",
    "pow",
    "ham",
    "Kid",
    "samm",
    "lmao",
    "XD",
    "Bio",
    "damn",
    "beaver",
    "werd",
    "igloo",
    "dew",
    "emoji",
    "funny",
    "lion",
    "cow",
    "milk",
    "LMAO",
    "tick",
    "belt",
    "hot",
    "wow",
    "lay",
    "sit",
    "sun",
    "Fly",
    "Dad",
    "boy",
    "old",
    "No",
    "Gig",
    "due"
    "top",
    "nun",
    "Flu",
    "pen",
    "XDD",
    "ice",
    "Bad",
    "bag",
    "hen",
    "OP",
    "Owl"
    "Cow",
    "Pan",
    "cap",
    "tie",
    "bat",
    "Dawg",
    "Mug",
    "row",
    "car",
    "Hat",
    "Hita"
    "Tip",
    "few",
    "buy",
    "win",
    "Jet",
    "Mud",
    "tap",
    "Eep",
    "Map",
    "fan",
    "Oil",
    "ban",
    "pit",
    "bee",
    "aid",
    "EP",
    "Me",
    "Eye"
};


// Long word list if you want to add a word increase the array size to match it
const std::string LongWordList[66] =
{
    "thunder",
    "giraffe",
    "hangman",
    "destroy",
    "computer",
    "ratchet",
    "jetpack",
    "icecream",
    "computer",
    "dictionary",
    "algorithm",
    "technology",
    "cable",
    "controller",
    "dexterity",
    "keyboard",
    "thunderous",
    "blizzard",
    "hazardous",
    "destruction",
    "operation",
    "asignment",
    "dictionary",
    "Football",
    "orange",
    "Error",
    "Chocolate",
    "Basis",
    "piano",
    "World",
    "Virus",
    "music",
    "ladder",
    "Owner",
    "Truth",
    "knowledge",
    "Failure",
    "lady",
    "hax0r",
    "Health",
    "Pie",
    "Party",
    "Sammuel",
    "jackson",
    "Harry",
    "Michael",
    "Craig",
    "jessica",
    "STEVE",
    "killa",
    "Chicken",
    "Diamond",
    "Jacob",
    "Timer",
    "speedruna",
    "Apple",
    "eater",
    "dictionary",
    "Justin",
    "Kathy",
    "bigFAN",
    "Happiest",
    "XVIII",
    "Kevin",
    "Barry",
    "Bob"
};


// Function for getting time
std::string get_time()
{
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%d-%m-%Y %H-%M-%S");
    auto str = oss.str();

    return str;
}

// Function for generating a random string
std::string random_string(size_t length)
{
    auto randchar = []() -> char
    {
        const char charset[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[rand() % max_index];
    };
    std::string str(length, 0);
    std::generate_n(str.begin(), length, randchar);
    return str;
}

// Function for generating a random number string
std::string random_number(size_t length)
{
    auto randchar = []() -> char
    {
        const char charset[] =
            "0123456789";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[rand() % max_index];
    };
    std::string str(length, 0);
    std::generate_n(str.begin(), length, randchar);
    return str;
}

// Function for saving specified string to your clipboard for pasting
void toClipboard(const std::string& s) 
{
    OpenClipboard(0);
    EmptyClipboard();
    HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, s.size() + 1);
    if (!hg) {
        CloseClipboard();
        return;
    }
    memcpy(GlobalLock(hg), s.c_str(), s.size());
    GlobalUnlock(hg);
    SetClipboardData(CF_TEXT, hg);
    CloseClipboard();
    GlobalFree(hg);
}

int main()
{
    // gets current time for time stamp
    std::string timedate = get_time();

    // create ofstream variable
    std::ofstream file;
    // open account.txt file in same directory as exe
    file.open("accounts.txt", std::ios::ate | std::ios::app);
 
    // Enter timestamp on accounts.txt file
    file << "\n\nTime of making accounts: ";
    file << timedate;
    file << "\n";

    // declare some time variables
    time_t begin, end;

    // bool I turn for toggling to represent if password and username is being done, I dont know why I did it this way
    bool loginstringtype = true; // true is username, false is password

    std::cout << "\n\n\tEach time you press Control a new username & password\n\t gets saved to your clipboard and passwords.txt file\n\n" << "\n";

    while (1)
    {
        unsigned __int64 now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count(); // gets current time in ms for use in srand
        srand(now); // randomizes the rand function using current time variable, prevents the same values from occuring

        if (file.is_open()) // open accounts.txt file
        {

            if (GetAsyncKeyState(VK_CONTROL) & 1)
            {
                if (loginstringtype == true)
                {
                    std::string string; 

                    string += random_number((rand() % 1));

                    string += LongWordList[rand() % 66];

                    string += ShortWordList[rand() % 82];

                    string += random_number((rand() % 2) + 1);
                    
                    std::cout << "\tusername: " << string << "\n";

                    toClipboard(string);

                    file << "\t";

                    file << string;

                    file << ":";
                    
                    loginstringtype = false;
                }
                else
                {
                    std::string string = random_string(12);
                    toClipboard(string);
                    std::cout << "\tpassword: " << string << "\n\n";
                    
                    file << string;

                    file << "\n";

                    loginstringtype = true;
                }
            }
        }
        else
        {
            std::cout << "\tError: account.txt failed to open,\n\tmake sure its in the same directory as your exe";
        }
    }

}
