function js_to_python(js_code) {
    // Replace JavaScript syntax with Python syntax
    var python_code = js_code.replace(/console\.log\(/g, "print(");
    return python_code;
}

function python_to_js(python_code) {
    // Replace Python syntax with JavaScript syntax
    var js_code = python_code.replace(/print\(/g, "console.log(");
    return js_code;
}

// Example usage:
var python_code = `
function greet(name) {
    console.log("Hello, " + name + "!");
}

greet("world");
`;

var js_code = python_to_js(python_code);
console.log("JavaScript Code:");
console.log(js_code);

console.log("\nPython Code:");
console.log(js_to_python(js_code));
