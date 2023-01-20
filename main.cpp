#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <vector>
#include <cmath>
using namespace std;


class Node
{

public:

    char k;
    Node* left;
    Node* right;

    void Insert_prefix(string& expression)
    {
        k = expression[0];
        expression.erase(0, 1);
        if (!(int(k) <= 57 && int(k) >= 48) && expression.size())
        {
            left = new Node;
            left->left = nullptr;
            left->right = nullptr;
            left->Insert_prefix(expression);
            right = new Node;
            right->left = nullptr;
            right->right = nullptr;
            right->Insert_prefix(expression);
        }
    }

    void Insert_postfix(string& expression)
    {
        k = expression[expression.size() - 1];
        expression.erase(expression.size() - 1, 1);
        if (!(int(k) <= 57 && int(k) >= 48) && expression.size())
        {
            right = new Node;
            right->left = nullptr;
            right->right = nullptr;
            right->Insert_postfix(expression);
            left = new Node;
            left->left = nullptr;
            left->right = nullptr;
            left->Insert_postfix(expression);
        }
    }

    void Insert_infix(string expression)
    {
        int n = expression.size();
        int* a = new int[n];
        for (int i = 0; i < n; i++)
        {
            a[i] = 0;
        }
        for (int i = 0, t = 0; i < n; i++)
        {
            if (expression[i] == '(')
                t++;
            if (expression[i] == ')')
                t--;
            a[i] = t;
        }
        int j = 0, m = 9999999;
        for (int i = 0; i < n; i++)
        {
            if (a[i] <= m && i > j && !(int(expression[i]) <= 57 && int(expression[i]) >= 48) && !(expression[i] == '(') && !(expression[i] == ')'))
            {
                j = i;
                m = a[i];
            }
        }
        if (m == 9999999)
        {
            m = 0;
        }
        if (m != 0)
        {
            for (; m; m--)
            {
                expression.erase(0, 1);
                expression.erase(expression.size() - 1, 1);
                j--;
                n-=2;
            }
        }
        delete[] a;
        k = expression[j];
        if (!(int(k) <= 57 && int(k) >= 48) && expression.size())
        {
            if (j > 0 && j < expression.size() - 1)
            {
                left = new Node;
                left->left = nullptr;
                left->right = nullptr;
                left->Insert_infix(expression.substr(0, j));
            }
            if (j < expression.size() - 1)
            {
                right = new Node;
                right->left = nullptr;
                right->right = nullptr;
                right->Insert_infix(expression.substr(j + 1, expression.size() - j - 1));
            }
        }
    }

    void Insert_type(string type, string expression)
    {
        if (type == "infix")
            Insert_infix(expression);
        else if (type == "postfix")
            Insert_postfix(expression);
        else if (type == "prefix")
            Insert_prefix(expression);
    }

    int Height()
    {
        if (left == nullptr && right == nullptr)
        {
            return 0;
        }
        else if (left == nullptr && right != nullptr)
        {
            return right->Height() + 1;
        }
        else if (right == nullptr && left != nullptr)
        {
            return left->Height() + 1;
        }
        else
        {
            int l = left->Height();
            int r = right->Height();
            if (l > r)
            {
                return l + 1;
            }
            else if (l <= r)
            {
                return r + 1;
            }
        }
        return 1;
    }

    void Print_with_sons()
    {
        cout << k << " , left son is ";
        if (left != nullptr)
            cout << left->k << ", ";
        else cout << "None, ";
        cout << "right son is ";
        if (right != nullptr)
            cout << right->k << "\n";
        else cout << "None\n";
        if (left != nullptr)
            left->Print_with_sons();
        if (right != nullptr)
            right->Print_with_sons();
    }

    void to_postfix(string& answer)
    {
        if (int(k) <= 57 && int(k) >= 48)
        {
            answer += k;
            if (left != nullptr)
                left->to_postfix(answer);
            if (right != nullptr)
                right->to_postfix(answer);
        }
        else
        {
            if (left != nullptr)
                left->to_postfix(answer);
            if (right != nullptr)
                right->to_postfix(answer);
            answer += k;
        }
    }

    void to_prefix(string& answer)
    {
        if (!(int(k) <= 57 && int(k) >= 48))
        {
            answer += k;
            if (left != nullptr)
                left->to_prefix(answer);
            if (right != nullptr)
                right->to_prefix(answer);
        }
        else
        {
            if (left != nullptr)
                left->to_prefix(answer);
            if (right != nullptr)
                right->to_prefix(answer);
            answer += k;
        }
    }

    void to_infix(string& answer)
    {
        if (!(int(k) <= 57 && int(k) >= 48))
        {
            answer += '(';
            if (left != nullptr)
                left->to_infix(answer);
            answer += k;
            if (right != nullptr)
                right->to_infix(answer);
            answer += ')';
        }
        else
        {
            answer += k;
            if (left != nullptr)
                left->to_infix(answer);
            if (right != nullptr)
                right->to_infix(answer);
        }
    }

    vector<string> to_different(string type)
    {
        vector<string> answer (2);
        if (type == "infix")
        {
            answer[0] = "postfix: ";
            to_postfix(answer[0]);

            answer[1] = "prefix: ";
            to_prefix(answer[1]);
        }
        else if (type == "postfix")
        {
            to_infix(answer[0]);
            int n = answer[0].size();
            int* a = new int[n];
            for (int i = 0; i < n; i++)
            {
                a[i] = 0;
            }
            for (int i = 0, t = 0; i < n; i++)
            {
                if (answer[0][i] == '(')
                    t++;
                if (answer[0][i] == ')')
                    t--;
                a[i] = t;
            }
            int j = 0, m = 9999999;
            for (int i = 0; i < n; i++)
            {
                if (a[i] <= m && i > j && !(int(answer[0][i]) <= 57 && int(answer[0][i]) >= 48) && !(answer[0][i] == '(') && !(answer[0][i] == ')'))
                {
                    j = i;
                    m = a[i];
                }
            }
            if (m == 9999999)
            {
                m = 0;
            }
            if (m != 0)
            {
                for (; m; m--)
                {
                    answer[0].erase(0, 1);
                    answer[0].erase(answer[0].size() - 1, 1);
                    j--;
                    n-=2;
                }
            }
            delete[] a;
            answer[0] = "infix: " + answer[0];

            answer[1] = "prefix: ";
            to_prefix(answer[1]);
        }
        else if (type == "prefix")
        {
            answer[0] = "postfix: ";
            to_postfix(answer[0]);

            to_infix(answer[1]);
            int n = answer[1].size();
            int* a = new int[n];
            for (int i = 0; i < n; i++)
            {
                a[i] = 0;
            }
            for (int i = 0, t = 0; i < n; i++)
            {
                if (answer[1][i] == '(')
                    t++;
                if (answer[1][i] == ')')
                    t--;
                a[i] = t;
            }
            int j = 0, m = 9999999;
            for (int i = 0; i < n; i++)
            {
                if (a[i] <= m && i > j && !(int(answer[1][i]) <= 57 && int(answer[1][i]) >= 48) && !(answer[1][i] == '(') && !(answer[1][i] == ')'))
                {
                    j = i;
                    m = a[i];
                }
            }
            if (m == 9999999)
            {
                m = 0;
            }
            cout << m << endl;
            if (m != 0)
            {
                for (; m; m--)
                {
                    answer[1].erase(0, 1);
                    answer[1].erase(answer[1].size() - 1, 1);
                    j--;
                    n-=2;
                }
            }
            delete[] a;
            answer[1] = "infix: " + answer[1];
        }
        return answer;
    }
};

class Tree
{
public:

    Node* Pnode;

    Tree()
    {
        Pnode = nullptr;
    }

    Tree(string type, string expression)
    {
        Pnode = new Node;
        Pnode->left = nullptr;
        Pnode->right = nullptr;
        Pnode->Insert_type(type, expression);
    }

    void Print_with_sons()
    {
        Pnode->Print_with_sons();
    }

    vector<string> to_different(string type)
    {
        return Pnode->to_different(type);
    }

};


int main()
{
    string type;
    getline(cin, type);
    string expression;
    getline(cin, expression);
    Tree tree(type, expression);
    //tree.Print_with_sons();
    vector<string> answer (2);
    answer = tree.to_different(type);
    cout << answer[0] << endl << answer[1];
    return 0;
}
