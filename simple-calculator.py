#!/usr/bin/env python3
"""
Advanced Calculator with GUI
A Python-based calculator with GUI interface supporting 
basic arithmetic operations and mathematical functions.
"""

import tkinter as tk
from tkinter import ttk, messagebox, font
import math
import re

class Calculator:
    def __init__(self, root):
        self.root = root
        self.root.title("Advanced Calculator")
        self.root.geometry("450x650")
        self.root.configure(bg='#2c3e50')
        self.root.resizable(False, False)
        
        # Set icon (optional)
        try:
            self.root.iconbitmap('calculator.ico')
        except:
            pass
        
        # Initialize variables
        self.current_input = ""
        self.result = ""
        self.memory = 0
        self.is_radians = True  # True for radians, False for degrees
        
        # Custom fonts
        self.display_font = font.Font(family="Consolas", size=20, weight="bold")
        self.button_font = font.Font(family="Arial", size=14)
        self.small_font = font.Font(family="Arial", size=10)
        
        # History
        self.history = []
        
        # Create UI
        self.create_widgets()
        self.create_menu()
        
        # Bind keyboard events
        self.root.bind('<Key>', self.key_press)
        
    def create_widgets(self):
        # Create main frame
        main_frame = tk.Frame(self.root, bg='#2c3e50')
        main_frame.pack(fill=tk.BOTH, expand=True, padx=10, pady=10)
        
        # Display Frame
        display_frame = tk.Frame(main_frame, bg='#34495e', relief=tk.RAISED, borderwidth=2)
        display_frame.pack(fill=tk.X, pady=(0, 10))
        
        # History label
        self.history_label = tk.Label(
            display_frame, 
            text="", 
            bg='#34495e', 
            fg='#7f8c8d', 
            font=self.small_font,
            anchor=tk.E,
            height=1
        )
        self.history_label.pack(fill=tk.X, padx=10, pady=(5, 0))
        
        # Display entry
        self.display_var = tk.StringVar()
        self.display = tk.Entry(
            display_frame,
            textvariable=self.display_var,
            font=self.display_font,
            bg='#ecf0f1',
            fg='#2c3e50',
            relief=tk.FLAT,
            justify=tk.RIGHT,
            bd=10,
            insertwidth=4,
            insertbackground='#e74c3c'
        )
        self.display.pack(fill=tk.X, padx=10, pady=(0, 10))
        self.display.focus_set()
        
        # Mode indicator
        mode_frame = tk.Frame(main_frame, bg='#2c3e50')
        mode_frame.pack(fill=tk.X, pady=(0, 10))
        
        self.mode_label = tk.Label(
            mode_frame,
            text="RAD",
            bg='#e74c3c',
            fg='white',
            font=self.small_font,
            padx=5,
            pady=2
        )
        self.mode_label.pack(side=tk.LEFT)
        
        self.memory_label = tk.Label(
            mode_frame,
            text="",
            bg='#2c3e50',
            fg='#3498db',
            font=self.small_font,
            padx=5
        )
        self.memory_label.pack(side=tk.RIGHT)
        
        # Button Frames
        scientific_frame = tk.Frame(main_frame, bg='#2c3e50')
        scientific_frame.pack(fill=tk.BOTH, expand=True)
        
        basic_frame = tk.Frame(main_frame, bg='#2c3e50')
        basic_frame.pack(fill=tk.BOTH, expand=True)
        
        # Scientific Buttons (2 rows)
        scientific_buttons = [
            # Row 1
            [('sin', self.sin_func), ('cos', self.cos_func), ('tan', self.tan_func), 
             ('log', self.log_func), ('ln', self.ln_func), ('π', self.add_pi)],
            
            # Row 2
            [('√', self.sqrt_func), ('x²', self.square), ('x³', self.cube), 
             ('xʸ', self.power), ('e', self.add_e), ('n!', self.factorial)],
            
            # Row 3
            [('(', self.add_char), (')', self.add_char), ('|x|', self.absolute), 
             ('1/x', self.reciprocal), ('10ˣ', self.power_10), ('2ˣ', self.power_2)]
        ]
        
        for row_idx, row in enumerate(scientific_buttons):
            for col_idx, (text, command) in enumerate(row):
                btn = tk.Button(
                    scientific_frame,
                    text=text,
                    font=self.button_font,
                    bg='#3498db',
                    fg='white',
                    activebackground='#2980b9',
                    activeforeground='white',
                    relief=tk.RAISED,
                    borderwidth=2,
                    height=2,
                    width=5,
                    command=lambda cmd=command, txt=text: self.button_click(cmd, txt)
                )
                btn.grid(row=row_idx, column=col_idx, padx=2, pady=2, sticky="nsew")
                scientific_frame.grid_columnconfigure(col_idx, weight=1)
        
        # Basic Calculator Buttons
        basic_buttons = [
            # Row 1
            [('MC', self.memory_clear), ('MR', self.memory_recall), ('M+', self.memory_add), 
             ('M-', self.memory_subtract), ('MS', self.memory_store), ('⌫', self.backspace)],
            
            # Row 2
            [('C', self.clear), ('±', self.toggle_sign), ('%', self.percentage), 
             ('÷', self.add_operator), ('π', self.add_pi), ('e', self.add_e)],
            
            # Row 3
            [('7', self.add_digit), ('8', self.add_digit), ('9', self.add_digit), 
             ('×', self.add_operator), ('x²', self.square), ('√', self.sqrt_func)],
            
            # Row 4
            [('4', self.add_digit), ('5', self.add_digit), ('6', self.add_digit), 
             ('-', self.add_operator), ('(', self.add_char), (')', self.add_char)],
            
            # Row 5
            [('1', self.add_digit), ('2', self.add_digit), ('3', self.add_digit), 
             ('+', self.add_operator), ('log', self.log_func), ('ln', self.ln_func)],
            
            # Row 6
            [('0', self.add_digit), ('.', self.add_decimal), ('=', self.calculate), 
             ('sin', self.sin_func), ('cos', self.cos_func), ('tan', self.tan_func)]
        ]
        
        for row_idx, row in enumerate(basic_buttons):
            for col_idx, (text, command) in enumerate(row):
                if text in ['=', 'C']:
                    bg_color = '#e74c3c'  # Red for equals and clear
                elif text in ['÷', '×', '-', '+', '%', '±']:
                    bg_color = '#f39c12'  # Orange for operators
                elif text in ['MC', 'MR', 'M+', 'M-', 'MS']:
                    bg_color = '#9b59b6'  # Purple for memory
                else:
                    bg_color = '#34495e'  # Dark blue for numbers
                
                btn = tk.Button(
                    basic_frame,
                    text=text,
                    font=self.button_font,
                    bg=bg_color,
                    fg='white',
                    activebackground='#2c3e50',
                    activeforeground='white',
                    relief=tk.RAISED,
                    borderwidth=2,
                    height=2,
                    width=7,
                    command=lambda cmd=command, txt=text: self.button_click(cmd, txt)
                )
                btn.grid(row=row_idx, column=col_idx, padx=2, pady=2, sticky="nsew")
                basic_frame.grid_columnconfigure(col_idx, weight=1)
        
    def create_menu(self):
        menubar = tk.Menu(self.root)
        self.root.config(menu=menubar)
        
        # File menu
        file_menu = tk.Menu(menubar, tearoff=0)
        menubar.add_cascade(label="File", menu=file_menu)
        file_menu.add_command(label="Clear History", command=self.clear_history)
        file_menu.add_separator()
        file_menu.add_command(label="Exit", command=self.root.quit)
        
        # Edit menu
        edit_menu = tk.Menu(menubar, tearoff=0)
        menubar.add_cascade(label="Edit", menu=edit_menu)
        edit_menu.add_command(label="Copy", command=self.copy_to_clipboard)
        edit_menu.add_command(label="Paste", command=self.paste_from_clipboard)
        
        # View menu
        view_menu = tk.Menu(menubar, tearoff=0)
        menubar.add_cascade(label="View", menu=view_menu)
        view_menu.add_command(label="Show History", command=self.show_history)
        
        # Mode menu
        mode_menu = tk.Menu(menubar, tearoff=0)
        menubar.add_cascade(label="Mode", menu=mode_menu)
        mode_menu.add_radiobutton(label="Radians", variable=tk.BooleanVar(value=True), 
                                 command=lambda: self.toggle_mode(True))
        mode_menu.add_radiobutton(label="Degrees", variable=tk.BooleanVar(value=False), 
                                 command=lambda: self.toggle_mode(False))
        
        # Help menu
        help_menu = tk.Menu(menubar, tearoff=0)
        menubar.add_cascade(label="Help", menu=help_menu)
        help_menu.add_command(label="About", command=self.show_about)
        help_menu.add_command(label="Keyboard Shortcuts", command=self.show_shortcuts)
        
    def button_click(self, command, text):
        """Handle button clicks"""
        command(text)
        
    def add_digit(self, digit):
        """Add digit to current input"""
        self.current_input += digit
        self.display_var.set(self.current_input)
        
    def add_operator(self, operator):
        """Add operator to current input"""
        operators = {'+': '+', '-': '-', '×': '*', '÷': '/', 'xʸ': '**'}
        if operator in operators:
            operator = operators[operator]
        
        if self.current_input and self.current_input[-1] not in '+-*/':
            self.current_input += operator
            self.display_var.set(self.current_input)
        elif operator == '-':  # Allow negative numbers
            self.current_input += operator
            self.display_var.set(self.current_input)
            
    def add_decimal(self, decimal):
        """Add decimal point"""
        if self.current_input.count('.') < 1 or not self.current_input[-1].isdigit():
            self.current_input += '.'
            self.display_var.set(self.current_input)
            
    def add_char(self, char):
        """Add character (parentheses)"""
        self.current_input += char
        self.display_var.set(self.current_input)
        
    def clear(self, text=""):
        """Clear current input"""
        self.current_input = ""
        self.display_var.set("")
        
    def clear_all(self):
        """Clear everything"""
        self.current_input = ""
        self.display_var.set("")
        self.history_label.config(text="")
        
    def backspace(self, text=""):
        """Remove last character"""
        self.current_input = self.current_input[:-1]
        self.display_var.set(self.current_input)
        
    def toggle_sign(self, text=""):
        """Toggle positive/negative sign"""
        if self.current_input:
            try:
                # Find the last number
                numbers = re.findall(r'[-+]?\d*\.?\d+', self.current_input)
                if numbers:
                    last_num = numbers[-1]
                    new_num = str(-float(last_num))
                    # Replace the last number
                    parts = self.current_input.rsplit(last_num, 1)
                    self.current_input = new_num.join(parts)
                    self.display_var.set(self.current_input)
            except:
                pass
                
    def percentage(self, text=""):
        """Calculate percentage"""
        try:
            if self.current_input:
                result = eval(self.current_input) / 100
                self.history_label.config(text=f"{self.current_input}% =")
                self.current_input = str(result)
                self.display_var.set(self.current_input)
        except:
            self.display_error("Invalid percentage calculation")
            
    def calculate(self, text=""):
        """Calculate the result"""
        if not self.current_input:
            return
            
        try:
            # Replace display symbols with Python operators
            expression = self.current_input
            expression = expression.replace('×', '*').replace('÷', '/')
            
            # Handle special constants
            expression = expression.replace('π', str(math.pi))
            expression = expression.replace('e', str(math.e))
            
            result = eval(expression)
            
            # Format result
            if isinstance(result, float):
                if result.is_integer():
                    result = int(result)
                else:
                    # Limit decimal places
                    result = round(result, 10)
                    
            self.history.append(f"{self.current_input} = {result}")
            self.history_label.config(text=f"{self.current_input} =")
            self.current_input = str(result)
            self.display_var.set(self.current_input)
            
        except ZeroDivisionError:
            self.display_error("Division by zero is not allowed")
        except ValueError as e:
            self.display_error(f"Math error: {str(e)}")
        except Exception as e:
            self.display_error(f"Invalid expression: {str(e)}")
            
    def display_error(self, message):
        """Display error message"""
        self.history_label.config(text="Error")
        self.display_var.set("Error")
        messagebox.showerror("Calculation Error", message)
        self.current_input = ""
        
    # Scientific Functions
    def sin_func(self, text=""):
        """Calculate sine"""
        try:
            if self.current_input:
                value = float(self.current_input)
                if not self.is_radians:
                    value = math.radians(value)
                result = math.sin(value)
                self.history_label.config(text=f"sin({self.current_input}) =")
                self.current_input = str(round(result, 10))
                self.display_var.set(self.current_input)
        except:
            self.display_error("Invalid input for sine")
            
    def cos_func(self, text=""):
        """Calculate cosine"""
        try:
            if self.current_input:
                value = float(self.current_input)
                if not self.is_radians:
                    value = math.radians(value)
                result = math.cos(value)
                self.history_label.config(text=f"cos({self.current_input}) =")
                self.current_input = str(round(result, 10))
                self.display_var.set(self.current_input)
        except:
            self.display_error("Invalid input for cosine")
            
    def tan_func(self, text=""):
        """Calculate tangent"""
        try:
            if self.current_input:
                value = float(self.current_input)
                if not self.is_radians:
                    value = math.radians(value)
                result = math.tan(value)
                self.history_label.config(text=f"tan({self.current_input}) =")
                self.current_input = str(round(result, 10))
                self.display_var.set(self.current_input)
        except:
            self.display_error("Invalid input for tangent")
            
    def log_func(self, text=""):
        """Calculate base-10 logarithm"""
        try:
            if self.current_input:
                value = float(self.current_input)
                if value <= 0:
                    raise ValueError("Logarithm undefined for non-positive numbers")
                result = math.log10(value)
                self.history_label.config(text=f"log({self.current_input}) =")
                self.current_input = str(round(result, 10))
                self.display_var.set(self.current_input)
        except ValueError as e:
            self.display_error(str(e))
        except:
            self.display_error("Invalid input for logarithm")
            
    def ln_func(self, text=""):
        """Calculate natural logarithm"""
        try:
            if self.current_input:
                value = float(self.current_input)
                if value <= 0:
                    raise ValueError("Natural log undefined for non-positive numbers")
                result = math.log(value)
                self.history_label.config(text=f"ln({self.current_input}) =")
                self.current_input = str(round(result, 10))
                self.display_var.set(self.current_input)
        except ValueError as e:
            self.display_error(str(e))
        except:
            self.display_error("Invalid input for natural logarithm")
            
    def sqrt_func(self, text=""):
        """Calculate square root"""
        try:
            if self.current_input:
                value = float(self.current_input)
                if value < 0:
                    raise ValueError("Square root undefined for negative numbers")
                result = math.sqrt(value)
                self.history_label.config(text=f"√({self.current_input}) =")
                self.current_input = str(round(result, 10))
                self.display_var.set(self.current_input)
        except ValueError as e:
            self.display_error(str(e))
        except:
            self.display_error("Invalid input for square root")
            
    def square(self, text=""):
        """Calculate square"""
        try:
            if self.current_input:
                value = float(self.current_input)
                result = value ** 2
                self.history_label.config(text=f"({self.current_input})² =")
                self.current_input = str(round(result, 10))
                self.display_var.set(self.current_input)
        except:
            self.display_error("Invalid input for square")
            
    def cube(self, text=""):
        """Calculate cube"""
        try:
            if self.current_input:
                value = float(self.current_input)
                result = value ** 3
                self.history_label.config(text=f"({self.current_input})³ =")
                self.current_input = str(round(result, 10))
                self.display_var.set(self.current_input)
        except:
            self.display_error("Invalid input for cube")
            
    def power(self, text=""):
        """Calculate power"""
        self.current_input += '**'
        self.display_var.set(self.current_input)
        
    def power_10(self, text=""):
        """Calculate 10^x"""
        try:
            if self.current_input:
                value = float(self.current_input)
                result = 10 ** value
                self.history_label.config(text=f"10^({self.current_input}) =")
                self.current_input = str(round(result, 10))
                self.display_var.set(self.current_input)
        except:
            self.display_error("Invalid input for power of 10")
            
    def power_2(self, text=""):
        """Calculate 2^x"""
        try:
            if self.current_input:
                value = float(self.current_input)
                result = 2 ** value
                self.history_label.config(text=f"2^({self.current_input}) =")
                self.current_input = str(round(result, 10))
                self.display_var.set(self.current_input)
        except:
            self.display_error("Invalid input for power of 2")
            
    def factorial(self, text=""):
        """Calculate factorial"""
        try:
            if self.current_input:
                value = int(float(self.current_input))
                if value < 0:
                    raise ValueError("Factorial undefined for negative numbers")
                if value > 100:
                    raise ValueError("Value too large for factorial")
                result = math.factorial(value)
                self.history_label.config(text=f"({self.current_input})! =")
                self.current_input = str(result)
                self.display_var.set(self.current_input)
        except ValueError as e:
            self.display_error(str(e))
        except:
            self.display_error("Invalid input for factorial")
            
    def absolute(self, text=""):
        """Calculate absolute value"""
        try:
            if self.current_input:
                value = float(self.current_input)
                result = abs(value)
                self.history_label.config(text=f"|{self.current_input}| =")
                self.current_input = str(result)
                self.display_var.set(self.current_input)
        except:
            self.display_error("Invalid input for absolute value")
            
    def reciprocal(self, text=""):
        """Calculate reciprocal (1/x)"""
        try:
            if self.current_input:
                value = float(self.current_input)
                if value == 0:
                    raise ValueError("Cannot divide by zero")
                result = 1 / value
                self.history_label.config(text=f"1/({self.current_input}) =")
                self.current_input = str(round(result, 10))
                self.display_var.set(self.current_input)
        except ValueError as e:
            self.display_error(str(e))
        except:
            self.display_error("Invalid input for reciprocal")
            
    def add_pi(self, text=""):
        """Add π to input"""
        self.current_input += 'π'
        self.display_var.set(self.current_input)
        
    def add_e(self, text=""):
        """Add e to input"""
        self.current_input += 'e'
        self.display_var.set(self.current_input)
        
    # Memory Functions
    def memory_store(self, text=""):
        """Store value in memory"""
        try:
            if self.current_input:
                self.memory = float(self.current_input)
                self.memory_label.config(text=f"M: {self.memory}")
                messagebox.showinfo("Memory", f"Value {self.memory} stored in memory")
        except:
            self.display_error("Invalid value for memory storage")
            
    def memory_recall(self, text=""):
        """Recall value from memory"""
        if self.memory != 0:
            self.current_input = str(self.memory)
            self.display_var.set(self.current_input)
            
    def memory_clear(self, text=""):
        """Clear memory"""
        self.memory = 0
        self.memory_label.config(text="")
        messagebox.showinfo("Memory", "Memory cleared")
        
    def memory_add(self, text=""):
        """Add current value to memory"""
        try:
            if self.current_input:
                self.memory += float(self.current_input)
                self.memory_label.config(text=f"M: {self.memory}")
        except:
            self.display_error("Invalid value for memory addition")
            
    def memory_subtract(self, text=""):
        """Subtract current value from memory"""
        try:
            if self.current_input:
                self.memory -= float(self.current_input)
                self.memory_label.config(text=f"M: {self.memory}")
        except:
            self.display_error("Invalid value for memory subtraction")
            
    # Mode Functions
    def toggle_mode(self, radians):
        """Toggle between radians and degrees"""
        self.is_radians = radians
        if radians:
            self.mode_label.config(text="RAD", bg='#e74c3c')
        else:
            self.mode_label.config(text="DEG", bg='#3498db')
            
    # Utility Functions
    def copy_to_clipboard(self):
        """Copy current value to clipboard"""
        if self.current_input:
            self.root.clipboard_clear()
            self.root.clipboard_append(self.current_input)
            messagebox.showinfo("Clipboard", "Value copied to clipboard")
            
    def paste_from_clipboard(self):
        """Paste value from clipboard"""
        try:
            clipboard_content = self.root.clipboard_get()
            # Validate it's a number
            float(clipboard_content)
            self.current_input += clipboard_content
            self.display_var.set(self.current_input)
        except:
            messagebox.showerror("Paste Error", "Clipboard does not contain a valid number")
            
    def clear_history(self):
        """Clear calculation history"""
        self.history = []
        self.history_label.config(text="")
        messagebox.showinfo("History", "Calculation history cleared")
        
    def show_history(self):
        """Show calculation history"""
        if not self.history:
            messagebox.showinfo("History", "No calculations in history")
            return
            
        history_window = tk.Toplevel(self.root)
        history_window.title("Calculation History")
        history_window.geometry("400x300")
        history_window.configure(bg='#2c3e50')
        
        text_widget = tk.Text(
            history_window,
            bg='#34495e',
            fg='white',
            font=("Consolas", 12)
        )
        text_widget.pack(fill=tk.BOTH, expand=True, padx=10, pady=10)
        
        scrollbar = tk.Scrollbar(text_widget)
        scrollbar.pack(side=tk.RIGHT, fill=tk.Y)
        text_widget.config(yscrollcommand=scrollbar.set)
        scrollbar.config(command=text_widget.yview)
        
        for i, calc in enumerate(self.history, 1):
            text_widget.insert(tk.END, f"{i}. {calc}\n")
            
        text_widget.config(state=tk.DISABLED)
        
    def show_about(self):
        """Show about dialog"""
        about_text = """Advanced Calculator v1.0
        
A Python-based calculator with GUI interface
supporting basic arithmetic operations and 
mathematical functions.

Features:
• Basic arithmetic operations
• Scientific functions (sin, cos, tan, log, ln)
• Memory functions
• History tracking
• Keyboard support
• Radians/Degrees mode

Created with Tkinter

Developer: Hawi
Email: h13746080@gmail.com
GitHub: hawi1236"""
        
        messagebox.showinfo("About Calculator", about_text)
        
    def show_shortcuts(self):
        """Show keyboard shortcuts"""
        shortcuts = """Keyboard Shortcuts:
        
0-9: Numbers
+ : Addition
- : Subtraction
* : Multiplication
/ : Division
. : Decimal point
= or Enter: Calculate
Escape: Clear
Backspace: Delete last character
c : Copy
v : Paste
r : Square root
s : Sin
c : Cos
t : Tan
l : Log
n : Ln
p : π
e : e"""
        
        messagebox.showinfo("Keyboard Shortcuts", shortcuts)
        
    def key_press(self, event):
        """Handle keyboard events"""
        key = event.char
        keysym = event.keysym
        
        # Numbers
        if key in '0123456789':
            self.add_digit(key)
            
        # Operators
        elif key == '+':
            self.add_operator('+')
        elif key == '-':
            self.add_operator('-')
        elif key == '*':
            self.add_operator('×')
        elif key == '/':
            self.add_operator('÷')
            
        # Decimal point
        elif key == '.':
            self.add_decimal('.')
            
        # Calculate
        elif key in ('=', '\r', '\n'):  # Enter or =
            self.calculate()
            
        # Clear
        elif keysym == 'Escape':
            self.clear()
            
        # Backspace
        elif keysym == 'BackSpace':
            self.backspace()
            
        # Copy/Paste
        elif event.state & 4 and key == 'c':  # Ctrl+C
            self.copy_to_clipboard()
        elif event.state & 4 and key == 'v':  # Ctrl+V
            self.paste_from_clipboard()
            
        # Scientific functions (Ctrl+Key)
        elif event.state & 4:
            if key == 's':
                self.sin_func()
            elif key == 'c':
                self.cos_func()
            elif key == 't':
                self.tan_func()
            elif key == 'l':
                self.log_func()
            elif key == 'n':
                self.ln_func()
            elif key == 'r':
                self.sqrt_func()
            elif key == 'p':
                self.add_pi()
            elif key == 'e':
                self.add_e()

def main():
    """Main function to run the calculator"""
    root = tk.Tk()
    app = Calculator(root)
    root.mainloop()

if __name__ == "__main__":
    main()