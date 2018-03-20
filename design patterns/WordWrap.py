# Recursively divides a string into pieces, delineated by spaces
# then adds them to a list, where each list_item would be a 'line'
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
def ConvertBuffer(max_chars, line_buffer):
    for index, line in enumerate(line_buffer):
        if len(line) > max_chars:
            line_buffer[index] = WordWrap(max_chars, line)
        else:
            line_buffer[index] = [line]

    return line_buffer


s = ["This is a short line.", "This is a very super massive big ginormous line.", "This is a third huge but not unsustainanble line", "Line fin"]

print(ConvertBuffer(20, s))


# This is how to store long strings in python
s = ("Lorem Ipsum has been the industry's standard dummy text ever since the 1500s, "
    "when an unknown printer took a galley of type and scrambled "
    "it to make a type specimen book. It has survived not only five centuries, "
    "but also the leap into electronic typesetting, remaining essentially unchanged. "
    "It was popularised in the 1960s with the release of Letraset sheets containing "
    "Lorem Ipsum passages, and more recently with desktop publishing software like "
    "Aldus PageMaker including versions of Lorem Ipsum.")

result = WordWrap(64, s)

# For some reason printing the result causes the first item to use double quotes and the rest to use single.
for s in result:
    print(type(s))


print(result)

