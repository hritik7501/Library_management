#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <iterator>

#define MAX 50

class Books
{
public:
    Books(std::string &title, std::string &author, std::string &publisher, int price)
        : Title{title}, Author{author}, Publisher{publisher}, Price{price} {};
    auto incrementStock()
    {
        this->Stocks++;
    }
    auto showStocks()
    {
        return Stocks;
    }
    auto fetchStocks(int requirement)
    {
        this->Stocks -= requirement;
    }
    auto getPrice()
    {
        return Price;
    }
    auto display()
    {
        std::cout << "Title: " << this->Title << "\n";
        std::cout << "Author: " << this->Author << "\n";
        std::cout << "Publisher: " << this->Publisher << "\n";
        std::cout << "Price: " << this->Price << "\n";
    }

private:
    std::string Title{},
        Author{},
        Publisher{};
    int Price{},
        Stocks{1};
};

int main()
{
    int num = 0,
        diffBooks = 0;
    std::unordered_map<std::string, Books *> myInventory;
    std::unordered_set<std::string> TitlesAndAuthors;

    std::cout << "To Install Books into the Inventory press 1, else -1: ";
    std::cin >> num;
    while (num == 1) //Inventory Setup
    {
        diffBooks++;
        std::cout << "Enter Book details-:\n";
        getchar();
        std::cout << "Title: ";
        std::string title;
        getline(std::cin, title);

        std::cout << "Author: ";
        std::string author;
        getline(std::cin, author);
        std::cout << "Publisher: ";
        std::string publisher;
        getline(std::cin, publisher);
        std::cin.clear();
        std::cout << "Price: ";
        int price;
        std::cin >> price;
        auto requestedCheck = title + author;
        TitlesAndAuthors.insert(requestedCheck);
        Books *ptrBook = NULL;
        if (int(TitlesAndAuthors.size()) != diffBooks)
        {
            myInventory[title]->incrementStock();
            diffBooks--;
        }
        else
        {
            ptrBook = new Books(title, author, publisher, price);
            myInventory.insert({title, ptrBook});
        }
        //title.clear(); author.clear(); publisher.clear();
        std::cout << "Press 1 to Insert another book in the Inventory & 0 to stop: ";
        std::cin >> num;
    }

    { //Invalidation Check
        if (num == 0)
        {
            std::cout << "Successfully Installed All The Books In The Inventory\n";
            num = 1;
        }
        else
        {
            std::cout << "Inventory Is Empty\n";
            return -1;
        }
    }

    while (num) //Querying The System
    {
        std::cout << "Enter the Required Book Title: ";
        getchar();
        std::string title;
        getline(std::cin, title);
        std::cout << "Enter the Required Book Author: ";
        std::string author;
        getline(std::cin, author);
        auto requestedCheck = title + author;
        if (TitlesAndAuthors.find(requestedCheck) == end(TitlesAndAuthors))
        {
            std::cout << "The Requested Book is not available\n";
        }
        else
        {
            std::cout << "The Requested Book is available\nPlease specify the required number of copies: ";
            int stock;
            std::cin >> stock;
            if (stock <= myInventory[title]->showStocks())
            {

                int price = 0;
                std::cout << "Required copies are in stock\n";
                myInventory[title]->display();
                price = myInventory[title]->getPrice();
                price *= stock;
                std::cout << "The Total Cost of your Order is: " << price << "\n";
                myInventory[title]->fetchStocks(stock);
            }
            else
                std::cout << "Required copies are not in stock\n";
        }
        std::cout << "Press 1 to CheckOut another book in the Inventory & 0 to stop: ";
        std::cin >> num;
        std::cin.clear();
    }
    return 0;
}
