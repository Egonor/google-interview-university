#prototype.py

# Uses a collection to store a group of items that are made from a single base item.
# The base item can be generated beforehand so clones can be created at run-time or
# with faster speed.  


import copy

# Ideally this class wouldn't have patties and the entire thing would be built
# from a base prototype (because then we could have veggie burgeres, chicken patties, etc.)
class PrototypeBurger:
    def __init__(self):
        self.num_patties = 0
        self.patty_type = 'beef'
        self.toppings = []

    def AddToppings(self, *toppings):
        for topping in toppings:
            self.toppings.append(topping)

    # Does two things, makes sense here but probably isn't very object-oriented
    # Should probably Add single patty with better "meat checking"
    def AddPatties(self, num_patties, patty_type):
        self.num_patties = num_patties
        self.patty_type = patty_type

    def Serve(self):
        print("Order Up! One {0} burger with {1} patt".format(
                                        self.patty_type,
                                        self.num_patties), end="")
        if (self.num_patties == 1):
            print("y", end="")
        else:
            print("ies", end="")

        it = 0
        while (it < len(self.toppings)):
            print(self.toppings[it], end=", ")
            it += 1

        print(".")


class Burger:
    def __init__(self, test_list):
        self.test_list = test_list

    def get_new(self):
        test_list = ['new', 'copy']
        return self.__class__(test_list)


# Make a burger prototype and collection
prototype_burger = PrototypeBurger()
orders = []

cheese_burger = copy.deepcopy(prototype_burger)
cheese_burger.AddPatties(2, 'beef')
cheese_burger.AddToppings('cheese')

print(cheese_burger.toppings)

let_and_tom_burger = copy.deepcopy(prototype_burger)
let_and_tom_burger.AddPatties(1, 'chicken')
let_and_tom_burger.AddToppings('lettuce')
print(cheese_burger.toppings)
let_and_tom_burger.AddToppings('tomato')
print(cheese_burger.toppings)


cheese_burger.Serve()
let_and_tom_burger.Serve()


print("-----------")
test = Burger(['test', 'list'])
foo = test.get_new()


print(test.test_list)
print(foo.test_list)
