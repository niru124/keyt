# Keyt - Terminal UI Keyboard Tester

**Keyt** is a lightweight terminal-based keyboard tester built with [FTXUI](https://github.com/ArthurSonzogni/FTXUI). It uses `evtest` to detect keypresses and provides a simple interactive TUI to visualize your keyboard layout in real time.

---

## 🚀 Getting Started

Follow these steps to clone, set up, and run **Keyt**:

```bash
git clone https://github.com/niru124/keyt
cd keyt
chmod +x runi.sh
./runi.sh
````

> Make sure you have the necessary permissions to run `evtest`. You may need to run the script with `sudo` depending on your system.

---

## 🧩 Features

* Select your keyboard input device via a TUI
* Visualize your keypresses in real time
* Works with various keyboard layouts
* Built with the modern and beautiful [FTXUI](https://github.com/ArthurSonzogni/FTXUI)

---

## 🕹️ Usage

1. **Run the app**:
   `sudo ./runi.sh`

2. **Select a keyboard layout**:
   Navigate the TUI and choose your keyboard device from the list.

3. **Confirm your choice**:
   Press `Ctrl+C` once the correct device is selected.

4. **Start typing**:
   Begin pressing keys to see them detected and visualized in the TUI. Keyt uses `evtest` under the hood for accurate key event tracking.

---

## 🛠️ Requirements

* Linux system
* `evtest` (usually preinstalled or available via your package manager)
* C++ compiler
* [FTXUI](https://github.com/ArthurSonzogni/FTXUI)

---

## 📦 Build Notes

If you're modifying or building from source, make sure FTXUI and any dependencies are available on your system. The project uses `runi.sh` to handle the runtime setup and execution.

---

## 🧪 Disclaimer

This tool uses `evtest`, which require root privileges. 
