#include <iostream>
using namespace std;
#include "bst.h"
#include "tree_functions.cpp"
#include "operator_overloading.cpp"

int main(){
    int testCase = 1;
    cout << "Please enter the test case number: ";
    cin >> testCase;
    cout << endl;

    cout << "============================================" << endl;
    cout << "Showing the output for test case " << testCase << ":" << endl;

    if (testCase==1){
        int virus_sequence[] = {1,4,2,6};
        BST<int> virus_tree;
        for (int i = 0; i<4; i++){
            virus_tree.insert(virus_sequence[i]);
        }
        cout<<endl;
        cout<<"Step 1: Tree output after adding nodes with values: 1, 4, 2, 6"<<endl;
        cout<<endl;
        virus_tree.print();
        cout<<endl;
        cout<<"Step 2: Tree output after adding nodes with values: 1, 4"<<endl;
        cout<<endl;
        int virus_sequence2[] = {1,4};
        for (int i = 0; i<2; i++){
            virus_tree.insert(virus_sequence2[i]);
        }
        virus_tree.print();
        int virus_sequence3[] = {1,4,5,2,3,8,9};
        BST<int> virus_tree2;
        for (int i = 0; i<7; i++){
            virus_tree2.insert(virus_sequence2[i]);
        }
        virus_tree = virus_tree+virus_tree2;
        
        virus_tree.print();
        cout<<endl;
        cout<<"step 3: "<<virus_tree[1];
        cout<<endl;
        cout<<"total node"<<virus_tree.totalNodes()<<endl;

    }
    else if (testCase==2){
        // Testing getMaxHeight function
        int virus_sequence[] = {1,4,5,2,3,8,9};
        BST<int> virus_tree;
        for (int i = 0; i<7; i++){
            virus_tree.insert(virus_sequence[i]);
        }
        virus_tree.print();
        cout<<"Maximum height of the tree: "<<virus_tree.getMaxHeight()<<endl;
        for(int i = 0; i<virus_tree.totalNodes();i++)
        {
            cout<<virus_tree[i]<<endl;
        }
    }
    else if (testCase==3){
        // Testing getMaxCounter function
        int virus_sequence[] = {1,2,2,3,3,3,4,5,5,6};
        BST<int> virus_tree;
        for (int i = 0; i<10; i++){
            virus_tree.insert(virus_sequence[i]);
        }
        virus_tree.print();
        cout<<"Maximum counter present in the tree: "<<virus_tree.getMaxcounter()<<endl;
    }
    else if (testCase==4){
        // Testing totalNodes function
        int virus_sequence[] = {1,2,2,3,3,3,4,5,5,6};
        BST<int> virus_tree;
        for (int i = 0; i<10; i++){
            virus_tree.insert(virus_sequence[i]);
        }
        virus_tree.print();
        cout<<"Total number of nodes in the tree: "<<virus_tree.totalNodes()<<endl;
    }
    else if (testCase==5){
        // Testing breakbond function
        int virus_sequence[] = {4,2,5,3,1,4,3,3,2,9};
        BST<int> virus_tree;
        for (int i = 0; i<10; i++){
            virus_tree.insert(virus_sequence[i]);
        }
        virus_tree.print();
        cout<<"Breaking bond with strength 2"<<endl;

        // Vaccine of strength 2 in action
        virus_tree.breakbond(2);
        virus_tree.print();
    }
    cout << "============================================" << endl << endl;
    return 0;
}

