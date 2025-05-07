class RectangleMemento:
    def __init__(self, width, height, color, Xposition, Yposition, layer):
        self.width = width
        self.height = height
        self.color = color
        self.Xposition = Xposition
        self.Yposition = Yposition
        self.layer = layer

class Rectangle:
    def __init__(self, width, height, color, Xposition, Yposition, layer):
        self.width = width
        self.height = height
        self.color = color
        self.Xposition = Xposition
        self.Yposition = Yposition
        self.layer = layer

    def create_memento(self):
        return RectangleMemento(self.width, self.height, self.color, self.Xposition,
                                self.Yposition, self.layer)

    def restore_from_memento(self, memento):
        self.width = memento.width
        self.height = memento.height
        self.color = memento.color
        self.Xposition = memento.Xposition
        self.Yposition = memento.Yposition
        self.layer = memento.layer

    def display(self):
        print(f"Rectangle(width={self.width}, height={self.height}, color='{self.color}', "
              f"Xposition ='{self.Xposition}', Yposition ='{self.Yposition}', layer={self.layer})")

class History:
    def __init__(self):
        self._history = []

    def save(self, memento):
        self._history.append(memento)

    def undo(self):
        if self._history:
            return self._history.pop()
        return None

rectangle = Rectangle(100, 50, 'red', 28, 44, 1)
history = History()

rectangle.display()

history.save(rectangle.create_memento())

rectangle.width = 200
rectangle.color = 'blue'
rectangle.layer = 3
rectangle.display()

memento = history.undo()
if memento:
    rectangle.restore_from_memento(memento)

rectangle.display()

