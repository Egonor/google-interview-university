# A Legacy Display that can only print from
#   a page buffer
# This code is provided 'as is' and cannot be modified.
class LegacyDisplay:

    def DrawPage(self, page_buffer):
        for line_num in range(0, 10):
            print(page_buffer[line_num])   

    def Clear(self):
        for i in range(11):
            print(' ')    # Line Numbers

# Adapter/Wrapper Class
#   - Holds an instance of the adaptee(LegacyDisplay)
class DisplayWrapper:

    def __init__(self):
        self._legacy_display = LegacyDisplay()
        self._char_limit = 64   # LegacyDisplay specific.
        self._line_limit = 10   # The LegacyDisplay can only output
                                # 30 characters in a line
                                # and 12 lines to a page: 1 Header, 1 Input

        self._page_cursor = 0
        self._print_buffer = []
        self._input_line = ">"   # The last line is used for user prompts.

    def WordWrap(char_limit, line_to_wrap):
        if len(line_to_wrap) <= char_limit:            
            return [line_to_wrap]

        mid = char_limit
        while line_to_wrap[mid] != ' ' and mid > 0:
            mid -= 1

        #print(line_to_wrap[:mid])

        return [line_to_wrap[:mid]] + WordWrap(char_limit, line_to_wrap[mid+1:])

    # Converts a list of lines to a 2D Array with 
    #  long lines turning into a list of line pieces.
    def ConvertBuffer(self, max_chars, line_buffer):
        for index, line in enumerate(line_buffer):
            if len(line) > max_chars:
                line_buffer[index] = WordWrap(max_chars, line)
            else:
                line_buffer[index] = [line]

        return line_buffer

    def PrintIt(self, header, input_text, app_buffer):    
        input_result = ''

        app_buffer = self.ConvertBuffer(self._char_limit, app_buffer)

        max_lines = self._line_limit
        if header == None:
            max_lines += 1
        else:            
            self._print_buffer.append(header)

        for line_list in app_buffer:
            for line_piece in line_list:
                if len(self._print_buffer) < max_lines:                             # Room for the Line
                    self._print_buffer.append(line_piece)
                else:                                                               # No Room
                    self._legacy_display.DrawPage(self._print_buffer)               # Draw the Page
                    input('More...')                                                # Fudged input
                    self._print_buffer.clear()                                      # Reset the Buffer
                    if header != None:                                              # Re-add header
                        self._print_buffer.append(header)
                    self._print_buffer.append(line_piece)                           # Add piece to new buffer

        # Pad short pages with blank space
        while len(self._print_buffer) < max_lines:
            self._print_buffer.append('')

        #print(self._print_buffer)
        self._legacy_display.DrawPage(self._print_buffer)
        input_result = input(input_text)
        self._print_buffer.clear()

        #print(input_result)
        return input_result
       
    # No modifications; called exactly
    def ClearPage(self):
        self._legacy_display.Clear()


# New Code/App
# class Customer():
#     def __init__(self, name, order_list):
#         #self._customerID = customer_id
#         self._customer_name = name
#         self._orders = order_list

class Order():
    def __init__(self, item_count, item_name):
        self.order_no = None
        #self.item_no = None
        self.item_count = item_count
        self.item_name = item_name

class NewApp():
    def __init__(self):
        self._display_adapter = DisplayWrapper()
        self._customer_data = {}
        self.header = ":::ADAPTEC CUSTOMER SERVICE:::"
        self.input_prompt = "Valid Input: <Customer Name>, 'all', or 'exit': "
        self._app_buffer = []

    def AddCustomer(self, customer_name, order_list):
        # Customer class...
        self._customer_data[customer_name] = order_list

    def RunApp(self):

        ### STARTUP SCREEN ###
        self._app_buffer.append("Current Customers:")
        for cust in self._customer_data:
            self._app_buffer.append(cust)
        input_val = self._display_adapter.PrintIt(self.header, self.input_prompt, self._app_buffer)
        ###                ###
        #print(input_val)

        while input_val != 'exit':
            self._app_buffer.clear()   # Clear buffer

            # Reprint Customer List
            if input_val == 'customers':                
                self._app_buffer.append("Current Customers:")
                for cust in self._customer_data.keys():
                    self._app_buffer.append(cust)
                input_val = self._display_adapter.PrintIt(self.header, self.input_prompt, self._app_buffer)

            # Print all Customers and their Orders
            elif input_val == 'all':
                for cust, orders in self._customer_data.items():
                    self._app_buffer.append(cust + ":")
                    for order in orders:
                        self._app_buffer.append("    " + str(order.item_count) + " " + order.item_name)

                input_val = self._display_adapter.PrintIt(self.header, self.input_prompt, self._app_buffer)

            # Print a specific Customer's Orders
            elif input_val in self._customer_data:
                self._app_buffer.append(input_val + ":")

                for order in self._customer_data[input_val]:
                    self._app_buffer.append("    " + str(order.item_count) + " " + order.item_name)

                input_val = self._display_adapter.PrintIt(self.header, self.input_prompt, self._app_buffer)

            # Handle bad input
            else:
                self._app_buffer.append("Invalid input.")
                input_val = self._display_adapter.PrintIt(self.header, self.input_prompt, self._app_buffer)



        # We're done
        self._app_buffer.clear()
        self._app_buffer.append(" ")
        self._app_buffer.append("     Thanks for using     ")
        self._app_buffer.append(" ")
        self._app_buffer.append(self.header)
        self._display_adapter.PrintIt(None, "Enter to quit...", self._app_buffer)
        #self._display_adapter.ClearPage()
            


ui = NewApp()

ui.AddCustomer("Michael Scott", [ Order(35, "Printers"), 
                                  Order(20, "Reams of Paper") ])
ui.AddCustomer("Peter Parker",  [ Order(18, "Rolls of Film"),
                                  Order(1, "Anatomy Arachnia Textbook") ])
ui.AddCustomer("Bruce Wayne",   [ Order(120, "Batarangs"),
                                  Order(3," Black Capes") ])
ui.AddCustomer("Clark Kent",    [ Order(13, "Pairs of Glasses") ])

ui.RunApp()