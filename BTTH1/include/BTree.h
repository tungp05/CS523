#ifndef BTREE_H
#define BTREE_H

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class BTreeNode {
public:
    bool Leaf;
    vector<string> Keys;
    vector<vector<int> > Values;
    vector<BTreeNode*> Children;

    BTreeNode(bool IsLeaf) {
        Leaf = IsLeaf;
    }
};

class BTree {
private:
    BTreeNode* Root;

    void SplitChild(BTreeNode* Parent, int i, BTreeNode* FullChild) {
        BTreeNode* NewNode = new BTreeNode(FullChild->Leaf);

        string MidKey = FullChild->Keys[1];
        vector<int> MidVal = FullChild->Values[1];

        NewNode->Keys.push_back(FullChild->Keys[2]);
        NewNode->Values.push_back(FullChild->Values[2]);

        if (!FullChild->Leaf) {
            NewNode->Children.push_back(FullChild->Children[2]);
            NewNode->Children.push_back(FullChild->Children[3]);

            FullChild->Children.erase(FullChild->Children.begin() + 2, FullChild->Children.end());
        }

        FullChild->Keys.erase(FullChild->Keys.begin() + 1, FullChild->Keys.end());
        FullChild->Values.erase(FullChild->Values.begin() + 1, FullChild->Values.end());

        Parent->Children.insert(Parent->Children.begin() + i + 1, NewNode);
        Parent->Keys.insert(Parent->Keys.begin() + i, MidKey);
        Parent->Values.insert(Parent->Values.begin() + i, MidVal);
    }

    void InsertNonFull(BTreeNode* Node, string Key, int RowIndex) {
        int i = (int)Node->Keys.size() - 1;

        if (Node->Leaf) {
            for (int j = 0; j < (int)Node->Keys.size(); j++) {
                if (Node->Keys[j] == Key) {
                    Node->Values[j].push_back(RowIndex);
                    return;
                }
            }

            Node->Keys.push_back("");
            Node->Values.push_back(vector<int>());

            while (i >= 0 && Key < Node->Keys[i]) {
                Node->Keys[i + 1] = Node->Keys[i];
                Node->Values[i + 1] = Node->Values[i];
                i--;
            }

            Node->Keys[i + 1] = Key;
            Node->Values[i + 1].push_back(RowIndex);
        }
        else {
            for (int j = 0; j < (int)Node->Keys.size(); j++) {
                if (Node->Keys[j] == Key) {
                    Node->Values[j].push_back(RowIndex);
                    return;
                }
            }

            while (i >= 0 && Key < Node->Keys[i]) i--;
            i++;

            InsertNonFull(Node->Children[i], Key, RowIndex);

            if ((int)Node->Children[i]->Keys.size() > 2) {
                SplitChild(Node, i, Node->Children[i]);
            }
        }
    }

    vector<int> search(BTreeNode* Node, string Key) {
        if (Node == NULL) return vector<int>();
        int i = 0;

        while (i < (int)Node->Keys.size() && Key > Node->Keys[i]) i++;
        if (i < (int)Node->Keys.size() && Key == Node->Keys[i]) {
            return Node->Values[i];
        }

        if (Node->Leaf) return vector<int>();

        return search(Node->Children[i], Key);
    }

    void PrintTree(BTreeNode* Node, int Level) {
        if (Node == NULL) return;
        cout << "Level " << Level << ": ";

        for (int i = 0; i < (int)Node->Keys.size(); i++) {
            cout << "[" << Node->Keys[i] << "] ";
        }
        cout << endl;

        for (int i = 0; i < (int)Node->Children.size(); i++) {
            PrintTree(Node->Children[i], Level + 1);
        }
    }

    void clear(BTreeNode* Node) {
        if (Node == NULL) return;
        for (int i = 0; i < (int)Node->Children.size(); i++) {
            clear(Node->Children[i]);
        }
        delete Node;
    }

public:
    BTree() {
        Root = NULL;
    }

    ~BTree() {
        clear(Root);
    }

    void insert(string Key, int RowIndex) {
        if (Root == NULL) {
            Root = new BTreeNode(true);
            Root->Keys.push_back(Key);
            Root->Values.push_back(vector<int>(1, RowIndex));
            return;
        }

        InsertNonFull(Root, Key, RowIndex);

        if ((int)Root->Keys.size() > 2) {
            BTreeNode* NewRoot = new BTreeNode(false);
            NewRoot->Children.push_back(Root);

            SplitChild(NewRoot, 0, Root);
            Root = NewRoot;
        }
    }

    vector<int> search(string Key) {
        return search(Root, Key);
    }

    void Reset() {
        clear(Root);
        Root = NULL;
    }

    void Print() {
        if (Root == NULL) {
            cout << "(Index rong)" << endl;
            return;
        }
        PrintTree(Root, 0);
    }
};

#endif // BTREE_H
