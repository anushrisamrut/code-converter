function pythonToJavaScript(pythonCode) {
    let javascriptCode = "";
    const lines = pythonCode.split('\n');

    for (let line of lines) {
        line = line.trim();
        if (line.startsWith("def")) {
            // Function definition
            const funcName = line.split("def ")[1].split("(")[0].trim();
            const parameters = line.split("(")[1].split(")")[0].trim();
            javascriptCode += `function ${funcName}(${parameters}) {\n`;
        } else if (line.trim().startsWith("return")) {
            // Return statement
            const value = line.split("return ")[1].trim();
            javascriptCode += `    return ${value};\n`;
        } else if (line.trim() === "") {
            // Empty line
            javascriptCode += "\n";
        } else {
            // Other statements (may need additional handling)
            javascriptCode += `    // ${line}\n`;
        }
    }

    return javascriptCode;
}

// Example Python code
const pythonCode = `
def add(a, b):
    return a + b

def multiply(x, y):
    return x * y
`;

// Convert Python code to JavaScript
const javascriptCode = pythonToJavaScript(pythonCode);
console.log("JavaScript Code:");
console.log(javascriptCode);
