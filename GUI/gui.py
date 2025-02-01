from tkinter import font
from time import sleep

import tkinter as tk
import threading
import serial


def update_state():
    port = "/dev/ttyACM0"
    baudrate = 115200
    ser = None

    while True:
        try:
            ser = serial.Serial(port, baudrate, timeout=0.5)
            break
        except Exception as e:
            print(f"No port: {e}")
            sleep(1)

    try:
        while True:
            line = ser.readline().decode("utf-8")

            if line:
                status_indicator.config(text="POVEZAN", fg="green")

                if "STATE CHANGE" in line:
                    state = line.split(":")[1].strip()
                    update_ui(state)
    finally:
        ser.close()


def update_ui(state):
    opened_box.config(bg="white")
    movement_box.config(bg="white")
    closed_box.config(bg="white")

    if state == "OPENED":
        opened_box.config(bg="green")
    elif state == "MOVEMENT":
        movement_box.config(bg="green")
    elif state == "CLOSED":
        closed_box.config(bg="green")
    else:
        opened_box.config(bg="yellow")
        movement_box.config(bg="yellow")
        closed_box.config(bg="yellow")


root = tk.Tk()
root.title("Monitor Stanja")
root.resizable(False, False)
root.geometry("684x208+550+200")

font_size = font.Font(size=20)

opened_box = tk.Label(
    root, text="OTVORENO", font=font_size, width=12, height=4, relief="solid"
)
opened_box.grid(row=0, column=0, padx=10, pady=10)

movement_box = tk.Label(
    root,
    text="OTVARANJE/\nZATVARANJE",
    font=font_size,
    width=12,
    height=4,
    relief="solid",
)
movement_box.grid(row=0, column=1, padx=10, pady=10)

closed_box = tk.Label(
    root, text="ZATVORENO", font=font_size, width=12, height=4, relief="solid"
)
closed_box.grid(row=0, column=2, padx=10, pady=10)

status_box = tk.Frame(root, relief="sunken")
status_box.grid(row=1, column=0, columnspan=3, padx=10, pady=10)

status_label = tk.Label(status_box, text="STATUS:", font=font_size)
status_label.grid(row=0, column=0, padx=10)

status_indicator = tk.Label(status_box, text="NEPOVEZAN", fg="red", font=font_size)
status_indicator.grid(row=0, column=1, padx=10)

state_thread = threading.Thread(target=update_state)
state_thread.daemon = True
state_thread.start()

root.mainloop()
