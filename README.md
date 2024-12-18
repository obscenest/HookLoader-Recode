# HookLoader-Recode

This project is a recoded and cleaned-up version of a Windows hook loader. It allows users to dynamically inject a DLL into a target window process using the `SetWindowsHookEx` function. The program has been modularized, and its logging system is enhanced for clarity with color-coded outputs.

---

## Features
- User-friendly console interface to input:
  - **Target Window Name**  
  - **DLL Name**  
  - **Exported Function Name**  
- Modularized code for better maintainability:
  - `Logger.hpp` for colorful, prefixed logs  
  - `WindowHooker.hpp` for hook-related operations  
- Enhanced error and success reporting using [termcolor](https://github.com/ikalnytskyi/termcolor).  
- Clean, structured project ready for further extension.

---

## Credits  
The original concept and code were inspired by [DrNseven's SetWindowsHookEx-Injector](https://github.com/DrNseven/SetWindowsHookEx-Injector).  
This recode includes refinements, modularization, and better logging.
