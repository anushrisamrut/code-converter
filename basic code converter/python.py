def python_to_js(python_code):
    # Replace Python syntax with JavaScript syntax
    js_code = python_code.replace("print(", "console.log(")
    return js_code

def js_to_python(js_code):
    # Replace JavaScript syntax with Python syntax
    python_code = js_code.replace("console.log(", "print(")
    return python_code

# Example usage:
python_code = """
def greet(name):
    print("Hello, " + name + "!")
    
greet("world")
"""

js_code = python_to_js(python_code)
print("JavaScript Code:")
print(js_code)

print("\nPython Code:")
print(js_to_python(js_code))
