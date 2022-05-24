
#include "sources/OrgChart.hpp"
#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <sstream>

using namespace ariel;
int main() {
    OrgChart organization;
    int ans;
    int a;
    int tmp1= true;
    int tmp= true;
    std::string n1;
    std::string n2;
    try{
        while (tmp1){
            cout << "to insert root send 1, sub root send 2 else 0 " << endl;
            cin>> ans;
            if (ans == 1) {
                string root;
                cout << "Please insert root 1" << endl;
                cin >> root;
                try {
                    organization.add_root(root);
                } catch (std::out_of_range ex) {
                        cout << ex.what() << endl;
                    }

            } else if (ans == 2) {
                cout << "Please insert  sub name 1" << endl;
                cin >> n1;
                cout << "Please insert  sub name 2" << endl;
                cin >> n2;
                try {
                    organization.add_sub(n1, n2);
                } catch (std::out_of_range ex) {
                    cout << ex.what() << endl;
                }

            }else{
                tmp1= false;
            }
        }
        while (tmp) {
            cout << "to level order send 1, revers send 2, proder 3 else to print 4 " << endl;
            cin>>ans;
             if (ans == 1) {
                for (auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it) {
                    cout << (*it) << " ";
                }
                 cout <<'\n';
            } else if (ans == 2) {
                for (auto it = organization.begin_reverse_order(); it != organization.reverse_order(); ++it) {
                    cout << (*it) << " ";
                }
                 cout <<'\n';
            } else if (ans == 3) {
                for (auto it = organization.begin_preorder(); it != organization.end_preorder(); ++it) {
                    cout << (*it) << " ";
                }
        } else if (ans ==4) {
                cout << organization;

        }else {
                tmp = false;
            }
        }
    } catch (std::out_of_range ex) {
        cout << ex.what() << endl;
    }
    return 0;
}
