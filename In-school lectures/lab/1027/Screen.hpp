#include <iostream>

// 窗口基类
class Window {
protected:
    int _x, _y, _w, _h;
};

// 派生类，用链表的形式将窗口组织起来
class WindowInScreen: public Window {
public:
    int id;
    WindowInScreen *next;
    WindowInScreen *prev;

    WindowInScreen(): next(nullptr) {}
    WindowInScreen(int id){
        this->id = id;
        next = nullptr;
        prev = nullptr;
    }
    void setX(int x){
        this->_x = x;
    }
    void setY(int y){
        this->_y = y;
    }
    void setW(int w){
        this->_w = w;
    }
    void setH(int h){
        this->_h = h;
    }
    int getH(){
        return _h;
    }
    int getW(){
        return _w;
    }
    int getX(){
        return _x;
    }
    int getY(){
        return _y;
    }

    void display() {
        // TODO
        std::cout << "(id: " << id << ", x: " << _x << ", y: " << _y << ", w: " << _w << ", h: " << _h << ")" << '\n';
        WindowInScreen *tmp = next;
        while (tmp != nullptr){
            std::cout << "(id: " << tmp->id << ", x: " << tmp->_x << ", y: " << tmp->_y << ", w: " << tmp->_w << ", h: " << tmp->_h << ")" << '\n';
            tmp = tmp->next;
        }
    }
};

// 屏幕类
class Screen {
    int _w, _h;
    int count;
    WindowInScreen *root;
    WindowInScreen *last;

public:
    Screen(int w = 1920, int h = 1080): _w(w), _h(h), count(0), root(nullptr), last(nullptr){}
    ~Screen() {
        // TODO
        count = 0;
        root = nullptr;
        last = nullptr;
    }

    void addWindow(int id) {
        // TODO
        WindowInScreen *window = new WindowInScreen(id);
        if (count == 0){
            window->setH(_h);
            window->setW(_w);
            window->setX(0);
            window->setY(0);
            window->next = nullptr;
            window->prev = nullptr;
            root = window;
            last = window;
            count++;
            return;
        }

        else if (count %2 == 1){
            window->setH(last->getH());
            window->setW(last->getW() / 2);
            window->setX((_w+last->getX()) / 2);
            window->setY(last->getY());
            last->setW(last->getW() / 2);
            window->prev = last;
            window->next = nullptr;
            last->next = window;
            last = window;
            count++;
        }
        else{
            window->setH(last->getH() / 2);
            window->setW(last->getW());
            window->setX(last->getX());
            window->setY((last->getY() + _h) / 2);
            last->setH(last->getH() / 2);
            window->prev = last;
            window->next = nullptr;
            last->next = window;
            last = window;
            count++;
        }

    }

    void delWindow(int id) {
        // TODO
        if (!last) return;
        if (count == 1){
            count = 0;
            root = nullptr;
            last = nullptr;
        }
        else if(last->id == id){
            count--;
            last = last->prev;
            last->next = nullptr;
            if (count % 2 == 1){
                last->setW(last->getW() * 2);
            }
            else{
                last->setH(last->getH() * 2);
            }
            
        }
        else{
            count--;
            WindowInScreen *target = root;
            while (target->id != id){
                target = target->next;
            }
            if (target == root){
                WindowInScreen *tmp = last;
                tmp->setX(tmp->prev->getX());
                tmp->setY(tmp->prev->getY());
                tmp->setW(tmp->prev->getW());
                tmp->setH(tmp->prev->getH());
                if (count % 2 == 1){
                    tmp->setW(tmp->getW() * 2);
                }
                else{
                    tmp->setH(tmp->getH() * 2);
                }
                tmp = tmp->prev;
                while (tmp != root){
                    tmp->setX(tmp->prev->getX());
                    tmp->setY(tmp->prev->getY());
                    tmp->setW(tmp->prev->getW());
                    tmp->setH(tmp->prev->getH());
                    tmp = tmp->prev;
                }
                root = root->next;
                root->prev = nullptr;
                return;
            }
            WindowInScreen *tmp = last;
            
            tmp->setX(tmp->prev->getX());
            tmp->setY(tmp->prev->getY());
            tmp->setW(tmp->prev->getW());
            tmp->setH(tmp->prev->getH());
            if (count % 2 == 1){
                tmp->setW(tmp->getW() * 2);
            }
            else{
                tmp->setH(tmp->getH() * 2);
            }
            tmp = tmp->prev;
            while (tmp != target){
                tmp->setX(tmp->prev->getX());
                tmp->setY(tmp->prev->getY());
                tmp->setW(tmp->prev->getW());
                tmp->setH(tmp->prev->getH());
                tmp = tmp->prev;
            }
            if (target->prev != nullptr) {
                target->prev->next = tmp->next;
                target->prev = nullptr;
                }
            if (target->next != nullptr){ 
                target->next->prev = tmp->prev;
                target->next = nullptr;
                }
        }
    }

    void display() {
        // TODO
        if (count == 0) return;
        root->display();
    }
};