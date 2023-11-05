#include <iostream>
#include <vector>
using namespace std;

struct dominoT
{
    int leftDots;
    int rightDots;
};

bool FormsDominoChain(vector<dominoT> &dominos)
{
    if (dominos.empty())
    {
        return true; // If all dominos have been used, we successfully formed a chain.
    }

    int prevRight = -1; // Initialize the previous right dots to an invalid value.

    for (size_t i = 0; i < dominos.size(); ++i)
    {
        if (prevRight == -1 || dominos[i].leftDots == prevRight)
        {
            // Try to connect the current domino to the previous one.
            int temp = dominos[i].leftDots;
            dominos[i].leftDots = dominos[i].rightDots;
            dominos[i].rightDots = temp;

            if (FormsDominoChain(dominos))
            {
                // Successfully connected the current domino to the chain.
                cout << dominos[i].leftDots << "|" << dominos[i].rightDots << " – ";
                return true;
            }

            // Reset the domino if the connection was unsuccessful.
            temp = dominos[i].leftDots;
            dominos[i].leftDots = dominos[i].rightDots;
            dominos[i].rightDots = temp;
        }
    }

    return false; // If no domino can be connected, the chain is impossible.
}

int main()
{
    vector<dominoT> dominoSet = {{1, 4}, {4, 3}, {3, 5}, {5, 2}, {2, 1}};

    if (FormsDominoChain(dominoSet))
    {
        cout << endl;
    }
    else
    {
        cout << "No valid domino chain found." << endl;
    }

    return 0;
}