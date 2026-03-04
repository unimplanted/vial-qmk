import json

def parse_keyboard_layout(layout, matrix = None):
    parsed_layout = layout
    parsed_row = []
    current_x = 0
    current_y = 0
    current_w = 0
    current_h = 0
    for row in layout:
        for key in row:
            parsed_key = {"matrix": [0, 0], "x": current_x, "y": current_y}  # 默认对象
            if isinstance(key, dict):  # If the element is a dictionary, it contains modifiers
                if 'x' in key:  # If there is an x modifier, update current_x
                    current_x += key['x']
                if 'y' in key:  # If there is a y modifier, update current_y
                    current_y += key['y']
                if 'w' in key:  # If there is a width modifier, update current_x for the next key
                    # current_x += key['w']  # Subtract 1 to account for the key itself
                    current_w = key['w']
                if 'h' in key:  # If there is a height modifier, update current_y for the next row
                    current_y += key['h'] - 1  # Subtract 1 to account for the row itself
                    current_h = key['h']
                if 'a' in key:  # If there is an absolute modifier, set current_x directly
                    current_x = key['a']
            elif isinstance(key, str):  # If the element is a string, it represents a key
                parsed_key["x"] = current_x
                parsed_key["y"] = current_y
                if current_w != 0:
                    parsed_key["w"] = current_w  # 更新宽度信息
                    current_x += current_w
                    current_x -=1
                    current_w = 0
                
                if current_h != 0:
                    parsed_key["h"] = current_h  # 更新宽度信息
                    current_h = 0
                
                parsed_row.append(parsed_key)
                current_x += 1  # Increment x after each key

        # parsed_layout.append(parsed_row)
        current_x = 0  # Reset current_x after each row
        current_y += 1  # Increment current_y for the next row

    current_x = 0
    current_y = 0
    via_json = []
    if matrix != None:
        key_index = 0
        for row in matrix:
            via_parsed_row = []
            for key in row:
                if isinstance(key, str):  # If the element is a string, it represents a key
                    parsed_row[key_index]["matrix"] = [current_y,current_x]
                    via_parsed_row.append(f"{current_y},{current_x}")
                    current_x += 1  # Increment x after each key
                    key_index+=1
                elif isinstance(key, dict):  # If the element is a dictionary, it contains modifiers
                    if 'x' in key:  # If there is an x modifier, update current_x
                        current_x += key['x']
                    via_parsed_row.append(key)
            
            via_json.append(via_parsed_row)
            current_y+=1
            current_x=0
    
    print(via_json)
    current_x = 0
    current_y = 0
    # via_json = []

    for row_raw, row_post in zip(layout, via_json):
        for key0,key1 in zip(row_raw, row_post):
            if isinstance(key0, str):  # If the element is a string, it represents a key
                if isinstance(key1, str):
                    pass
                else:
                    #row_post中的key1删除
                    del row_post[row_post.index(key1)]
                    pass
            else:
                #我需要在row_post的key1前面插入key0
                if key0 != key1:
                    if isinstance(key1, str):
                        index = row_post.index(key1)
                        row_post.insert(index, key0)
                    else:
                        #将key1的位置替换为key0
                        print(key1, key0)
                        index = row_post.index(key1)
                        row_post[index] = key0

    return parsed_row, via_json

# Test the function with the corrected layout
layout = [
    ["~\n`","!\n1","@\n2","#\n3","$\n4","%\n5","^\n6","&\n7","*\n8","(\n9",")\n0","_\n-","+\n=","Backspace","DEL"],
    [{"w":1.5},"Tab","Q","W","E","R","T","Y","U","I","O","P","{\n[","}\n]",{"w":1.5},"|\n\\"],
    [{"w":1.75},"Caps Lock","A","S","D","F","G","H","J","K","L",":\n;","\"\n'",{"w":2.25},"Enter"],
    [{"w":1.25},"LShift","LShift","Z","X","C","V","B","N","M","<\n,",">\n.","?\n/",{"w":1.75},"RShift","RShift"],
    [{"w":1.25},"Ctrl",{"w":1.25},"Win",{"w":1.25},"Alt",{"w":2},"sp",{"w":1.25},"sp",{"w":3},"sp",{"w":1.25},"Alt",{"w":1.25},"Win",{"w":1.25},"Menu",{"w":1.25},"Ctrl"]
]

matrix = [
    ["~\n`","!\n1","@\n2","#\n3","$\n4","%\n5","^\n6","&\n7","*\n8","(\n9",")\n0","_\n-","+\n=","Backspace"],
    ["Tab","Q","W","E","R","T","Y","U","I","O","P","{\n[","}\n]","|\n\\"],
    ["Caps Lock","A","S","D","F","G","H","J","K","L",":\n;","\"\n'","Enter","DEL"],
    ["Shift","|\n\\","Z","X","C","V","B","N","M","<\n,",">\n.","?\n/","Shift","FN"],
    ["Ctrl","Win","Alt",{"x":2},"sp","sp","sp",{"x":2},"Alt","Win","Menu","Ctrl"]
]

parsed_layout, via_json = parse_keyboard_layout(layout,matrix)

output_string = json.dumps(parsed_layout,indent=2)

output_string_cleaned = ''.join(output_string.split())

output_string_formatted = output_string_cleaned.replace("},", "},\n")

print(output_string_formatted)

via_json_output_string = json.dumps(via_json,indent=2)

via_output_string_cleaned = ''.join(via_json_output_string.split())

print(via_output_string_cleaned)
