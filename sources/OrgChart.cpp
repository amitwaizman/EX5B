#include "OrgChart.hpp"

using namespace ariel;

OrgChart::OrgChart() {
    this->head= nullptr;
}
OrgChart::OrgChart(const OrgChart &other) {
    this->head=other.head;
}

OrgChart &OrgChart::add_root(const std::string &root) {
    if((root=="\n")||(root==" ")){
        throw std::out_of_range{"not good!"};
    }
    if(this->head== nullptr){
        this->head=new Node{root};
    }else{
        this->head->name=root;
    }
    return *this;
}

OrgChart &OrgChart::add_sub(const std::string &str1, const std::string &str2) {
    if(this->head== nullptr||str1=="\n"||str1==" "||str2=="\n"||str2==" "){
        throw std::out_of_range{"empty!"};
    }
    for (iterator_oc i = this->begin_level_order(); i != this->end_level_order() ; ++i) {
        if((*i)==str1){
            Node* t=i.get();
            Node* n=new Node{str2};
            t->vecNext.push_back(n);
            return *this;
        }
    }
    throw std::out_of_range{"not exist!"};
}
OrgChart::iterator_oc::iterator_oc(Node *root, int status) {
    if(status==1){
        level_o(root);
    }else if(status==-1){
        revers_o(root);
    }else{
        preorder_o(root);
    }
    this->pointer= this->q.front();
}

Node *OrgChart::iterator_oc::get() {
    return this->pointer;
}

bool OrgChart::iterator_oc::operator!=(const iterator_oc &it) const {
    return !(*this==it);
}

bool OrgChart::iterator_oc::operator==(const iterator_oc &it) const {
    bool a=this->q.empty();
    bool b=it.q.empty();
    if ((!a) && (!b)) {
        return this->pointer == it.pointer;
    }
    return (a&&b);
}

std::string*  OrgChart::iterator_oc::operator->() const {
    return &(this->pointer->name);
}

std::string OrgChart::iterator_oc::operator*() const {
    return this->pointer->name;
}

OrgChart::iterator_oc &OrgChart::iterator_oc::operator++() {
    this->q.pop();
    this->pointer= this->q.front();
    return *this;
}

OrgChart::iterator_oc OrgChart::iterator_oc::operator++(int) {
    iterator_oc tmp=*this;
    this->q.pop();
    this->pointer= this->q.front();
    return tmp;
}
void OrgChart::iterator_oc::level_o(Node *root) {
    std::queue <Node*> tmp;
    tmp.push(root);
    while (!tmp.empty()) {
        this->pointer = tmp.front();
        tmp.pop();
        this->q.push(this->pointer);
        int h=this->pointer->vecNext.size();
        for (unsigned long i = 0; i < h; i++) {
            tmp.push(this->pointer->vecNext.at(i));
        }
    }
}

std::queue <Node*> OrgChart::iterator_oc::level_r( Node *root) {
    std::queue <Node*> tmp;
    std::queue <Node*> copy;
    tmp.push(root);
    while (!tmp.empty()) {
        Node* n = tmp.front();
        tmp.pop();
        copy.push(n);
        int h=(n->vecNext.size());
        for (unsigned long i =(unsigned long)h; i>0; --i) {
            tmp.push(n->vecNext.at(i-1));

        }
    }
    return copy;

}

void OrgChart::iterator_oc::revers_o( Node *root) {
    std::stack <Node*> s;
    std::queue <Node*> tmp=level_r(root);
    this->q=tmp;
    while (!this->q.empty()){
        this->pointer=this->q.front();
        s.push( this->pointer);
        this->q.pop();
    }
    while (!s.empty()){
        this->pointer=s.top();
        this->q.push( this->pointer);
        s.pop();
    }
}

void OrgChart::iterator_oc::preorder_o(Node *root) {
    if (root== nullptr) {
        return ;
    }
    this->pointer=root;
    this->q.push(this->pointer);
    for (unsigned long  i = 0; i <root->vecNext.size() ; ++i) {
        preorder_o(root->vecNext.at(i));
    }


}

OrgChart::iterator_oc OrgChart::begin_level_order() const {
    if(this->head== nullptr){
        throw std::out_of_range{"empty!"};
    }

    iterator_oc level{this->head,1};
    return level;
}

OrgChart::iterator_oc OrgChart::end_level_order() const {
    if(this->head== nullptr){
        throw std::out_of_range{"empty!"};
    }
    iterator_oc level;
    return level;
}

OrgChart::iterator_oc OrgChart::begin_reverse_order() const {
    if(this->head== nullptr){
        throw std::out_of_range{"empty!"};
    }
    iterator_oc revers{this->head,-1};
    return revers;
}
OrgChart::iterator_oc OrgChart::reverse_order() const {
    if(this->head== nullptr){
        throw std::out_of_range{"empty!"};
    }
    iterator_oc revers;
    return revers;
}

OrgChart::iterator_oc OrgChart::begin_preorder() const {
    if(this->head== nullptr){
        throw std::out_of_range{"empty!"};
    }
    iterator_oc pre{this->head,0};
    return pre;
}

OrgChart::iterator_oc OrgChart::end_preorder() const {
    if(this->head== nullptr){
        throw std::out_of_range{"empty!"};
    }
    iterator_oc pre;
    return pre;
}

OrgChart::iterator_oc OrgChart::end() const {
    return end_level_order();
}

OrgChart::iterator_oc OrgChart::begin() const {
    return begin_level_order();
}
queue <string>  ariel:: PrintOutput(const OrgChart &it) {
    std::queue <Node*> tmp;
    queue <string> copy;
    tmp.push(it.head);
    while (!tmp.empty()) {
        Node* n = tmp.front();
        tmp.pop();
        copy.push("~");
        copy.push(n->name);
        int h=(n->vecNext.size());
        for (unsigned long i = 0; i < h; i++) {
            tmp.push(n->vecNext.at(i));
            copy.push(n->vecNext.at(i)->name);
        }
    }

    return copy;
}

std::ostream&  ariel::operator<<( std::ostream &out, const OrgChart &it) {
    queue <string>  str=PrintOutput(it);
   while (!str.empty()){
        if("~"!=str.front()){
           str.pop();
           if(!str.empty()) {
               if("~"!=str.front()){
                   out<<"kid: "<<str.front()<<" ";
               }
            }
        } else{
            str.pop();
            if(!str.empty()){
            out<<"\nroot: ("<<str.front()<<")\n";
            }

        }
   }

    return out;
}

OrgChart::~OrgChart() {
    delete_N(this->head);
}

void OrgChart::delete_N(Node *root) {
    if (root == nullptr) {
        return;
    }
    for (unsigned long i = 0; i <root->vecNext.size(); ++i) {
        delete_N((root->vecNext.at(i)));
    }
    delete root;
}