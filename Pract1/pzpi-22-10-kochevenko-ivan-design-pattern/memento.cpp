#include <iostream>
#include <vector>
using namespace std;

class Rectangle {
private:
    int width, height;
    string color;
    int x, y;
    int layer;

public:
    Rectangle(int w, int h, const string& c, int x, int y, int l) : width(w), height(h), color(c), x(x), y(y), layer(l) {}

    void display() const {
        cout << "Rectangle(width=" << width
            << ", height=" << height
            << ", color=" << color
            << ", x=" << x
            << ", y=" << y
            << ", layer=" << layer << ")" << endl;
    }

    class Memento {
    private:
        int width, height;
        string color;
        int x, y;
        int layer;

        friend class Rectangle;

        Memento(int w, int h, const string& c, int x, int y, int l)
            : width(w), height(h), color(c), x(x), y(y), layer(l) {}

    public:
        Memento(const Memento& other) = default;
        ~Memento() = default;
    };

    Memento save() const {
        return Memento(width, height, color, x, y, layer);
    }

    void restore(const Memento& memento) {
        width = memento.width;
        height = memento.height;
        color = memento.color;
        x = memento.x;
        y = memento.y;
        layer = memento.layer;
    }
};

class History {
private:
    vector<Rectangle::Memento> history;

public:
    void save(const Rectangle::Memento& memento) {
        history.push_back(memento);
    }

    Rectangle::Memento undo() {
        if (!history.empty()) {
            Rectangle::Memento m = history.back();
            history.pop_back();
            return m;
        }
        throw runtime_error("History is empty!");
    }
};

int main() {
    Rectangle rect(100, 50, "red", 50, 40, 1);
    History history;

    rect.display();
    history.save(rect.save());

    rect = Rectangle(200, 100, "blue", 88, 41, 2);
    rect.display();

    rect.restore(history.undo());
    rect.display();

    return 0;
}
