import serial
import csv
import time
import pyautogui
import os

# === Serial Port Setup ===
try:
    ser = serial.Serial('COM3', 115200, timeout=1)
    print("✅ Serial port opened.", flush=True)
except serial.SerialException as e:
    print(f"❌ Serial Error: {e}", flush=True)
    exit()

# === CSV Setup ===
filename_csv = f"sensor_data_{time.strftime('%Y%m%d_%H%M%S')}.csv"
csv_file = open(filename_csv, "w", newline='')
writer = csv.writer(csv_file)
writer.writerow(["Millis", "Temperature", "Pressure", "Humidity", "Altitude", "IR Value"])
print(f"📝 Logging to: {filename_csv}", flush=True)

# === Screenshot Setup ===
screenshot_interval = 1800  # every 30 minutes
last_screenshot_time = time.time()
screenshot_dir = "screenshots"
os.makedirs(screenshot_dir, exist_ok=True)

# === Throttle Setup ===
log_interval = 1.0  # log once every second
last_log_time = time.time()

print("📸 Screenshots every 30 minutes → saved to /screenshots")
print("⏱ Logging every 1 second (skipping fast data). Press Ctrl+C to stop.\n", flush=True)

try:
    while True:
        line_bytes = ser.readline()
        try:
            line_raw = line_bytes.decode('utf-8', errors='ignore').strip()
        except Exception as e:
            print(f"⚠ Decode failed: {e}", flush=True)
            continue

        if not line_raw:
            continue

        values = [v.strip() for v in line_raw.split(',')]
        if len(values) == 6:
            current_time = time.time()

            # === Log only once per second ===
            if current_time - last_log_time >= log_interval:
                try:
                    writer.writerow(values)
                    print("✔", values, flush=True)
                    last_log_time = current_time
                except Exception as e:
                    print(f"❌ Write failed: {e}", flush=True)

            # === Screenshot every 30 minutes ===
            if current_time - last_screenshot_time >= screenshot_interval:
                try:
                    ts = time.strftime("%Y%m%d_%H%M%S")
                    screenshot_path = os.path.join(screenshot_dir, f"screenshot_{ts}.png")
                    pyautogui.screenshot(screenshot_path)
                    print(f"📸 Screenshot saved: {screenshot_path}", flush=True)
                    last_screenshot_time = current_time
                except Exception as e:
                    print(f"⚠ Screenshot error: {e}", flush=True)
        else:
            print(f"⚠ Malformed line (got {len(values)} values):", line_raw, flush=True)

except KeyboardInterrupt:
    print("\n🛑 Logging stopped by user.", flush=True)
finally:
    ser.close()
    csv_file.close()
    print("🔒 Serial port and file closed.", flush=True)
