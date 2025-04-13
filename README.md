# Parsing Script

A high-performance C++ script for parsing and processing data, designed for speed and efficiency using advanced compiler optimizations.

## 🚀 Features

- Efficient parsing using C++ and optimized compilation flags
- Converts PDF files to text using `pdftotext`
- Outputs results to `result.txt`

## 🛠 Requirements

Before running the script, make sure you have the following tools installed:

- **GCC Compiler**
- **pdftotext** tool (from `poppler-utils`)

### Install `poppler-utils` (for pdftotext)

If `pdftotext` is not installed on your system, you can install it using the following commands:

```bash
sudo apt-get update
sudo apt-get install poppler-utils
```
## 📁 Setup

1. **Clone the repository:**

   ```bash
   git clone https://github.com/your-username/parsing-script.git
   cd parsing-script
   ```
   
2. **Ensure the following two files are present in the same directory:**

   - `temp.out` – This file should contain the text to be parsed.  

   - `result.txt` – This file will store the output from the parser.  
     Create it (if it doesn’t already exist) using:
     ```bash
     touch result.txt
     ```

3. **Compile the C++ source file using the following command:**

   ```bash
   g++ -O3 -march=native -flto -funroll-loops main.cpp -o parser
   ```
   
4. **Run the script**

   ```bash
   ./parser.out
   ```
