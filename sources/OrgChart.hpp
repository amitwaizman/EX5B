#ifndef ORGCHART_A_ORGCHART_H
#define ORGCHART_A_ORGCHART_H
#include<vector>
#include <queue>
#include <stack>
#include <string>
#include <iostream>

using namespace std;
struct Node{
     string name;
     vector<Node*> vecNext;
};

namespace ariel {
    class OrgChart {
    private:
        Node* head;
    public:
        OrgChart();
        OrgChart(const OrgChart& other);
        ~OrgChart();
        void delete_N(Node* root);
        OrgChart& add_root(const string &root);
        OrgChart& add_sub(const string &str1, const string& str2);
        friend queue <string>  PrintOutput(const OrgChart &it);
        friend  ostream& operator<<( ostream &out, const OrgChart& it);

        class iterator_oc {
        private:
           queue<Node*> q;
            Node* pointer;
        public:

            iterator_oc(Node* ptr = nullptr):pointer(ptr){

            }
            iterator_oc(Node* root,int status);
            bool operator!=(const iterator_oc& it) const;
            bool operator==(const iterator_oc& it) const;
            string* operator->() const;
            string operator*() const;
            void level_o(Node* root);
            static queue <Node*> level_r( Node* root);
            void revers_o( Node* root);
            void preorder_o( Node* root);
            iterator_oc& operator++();
            iterator_oc operator++(int);
            Node* get();
        };
        iterator_oc begin_level_order() const;
        iterator_oc end_level_order() const;
        iterator_oc begin_reverse_order() const;
        iterator_oc reverse_order() const;
        iterator_oc begin_preorder()const;
        iterator_oc end_preorder() const;
        iterator_oc begin() const;
        iterator_oc end() const;
        OrgChart& operator=(const OrgChart& org);
        OrgChart& operator=(OrgChart&& org) noexcept;
        OrgChart( OrgChart && )noexcept;
    };
}

#endif //ORGCHART_A_ORGCHART_H
