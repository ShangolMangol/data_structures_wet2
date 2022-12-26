#include <iostream>
#include "AVLTree.h"
#include "CompareTeamById.h"
#include "memory"
#include "Team.h"

using std::shared_ptr;
using std::cout;
using std::endl;
using std::string;



// Print the tree
void printTree(AVLNode<shared_ptr<Team>> *root, string indent, bool last) {
    if (root != nullptr) {
        cout << "  ";
        if (last) {
            cout << "R----";
            indent += "   ";
        } else {
            cout << "L----";
            indent += "|  ";
        }
        cout << root->data->teamId << ", "<< root->sizeLeft << endl;
        printTree(root->left, indent, false);
        printTree(root->right, indent, true);
    }
}




int main()
{
    shared_ptr<Team> team1= shared_ptr<Team>(new Team(1));
    shared_ptr<Team> team2= shared_ptr<Team>(new Team(2));
    shared_ptr<Team> team88= shared_ptr<Team>(new Team(88));
    shared_ptr<Team> team165= shared_ptr<Team>(new Team(165));
    shared_ptr<Team> team170= shared_ptr<Team>(new Team(170));
    shared_ptr<Team> team60= shared_ptr<Team>(new Team(60));
    shared_ptr<Team> team55= shared_ptr<Team>(new Team(55));
    shared_ptr<Team> team3= shared_ptr<Team>(new Team(3));
    shared_ptr<Team> team4= shared_ptr<Team>(new Team(4));



    AVLTree<shared_ptr<Team>, CompareTeamById> avlTree;

    avlTree.root = avlTree.insert(avlTree.root, team1);
    avlTree.root = avlTree.insert(avlTree.root, team2);
    avlTree.root = avlTree.insert(avlTree.root, team88);
    avlTree.root = avlTree.insert(avlTree.root, team165);
    avlTree.root = avlTree.insert(avlTree.root, team170);
    avlTree.root = avlTree.insert(avlTree.root, team60);
    avlTree.root = avlTree.insert(avlTree.root, team55);

    avlTree.root = avlTree.deleteNode(avlTree.root, team2);

    avlTree.root = avlTree.insert(avlTree.root, team2);
    avlTree.root = avlTree.insert(avlTree.root, team3);
    avlTree.root = avlTree.insert(avlTree.root, team4);


//    printTree(avlTree.root, " ", false);

    return 0;
}
