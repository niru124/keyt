#!/bin/bash

echo "🔍 Step 1: Scanning for keyboard-capable event devices..."

keyboard_events=()
for event_path in /dev/input/event*; do
    if udevadm info --query=all --name="$event_path" | grep -q "ID_INPUT_KEYBOARD=1"; then
        event_name=$(basename "$event_path")
        keyboard_events+=("$event_name")
        echo "✅ Found keyboard device: $event_name"
    fi
done

if [ ${#keyboard_events[@]} -eq 0 ]; then
    echo "❌ No keyboard-capable devices found."
    exit 1
fi

echo -e "\n🔗 Step 2: Matching to /dev/input/by-id/ symlinks..."

declare -A event_to_byid
for dev in /dev/input/by-id/*; do
    [ -e "$dev" ] || continue
    target=$(readlink -f "$dev")
    event_name=$(basename "$target")

    if [[ " ${keyboard_events[*]} " == *" $event_name "* ]]; then
        event_to_byid["$event_name"]="$(basename "$dev")"
    fi
done

echo -e "\n📋 Step 3: Combined device list for selection:"
device_list=()
index=0
for event in "${keyboard_events[@]}"; do
    if [ -n "${event_to_byid[$event]}" ]; then
        label="${event_to_byid[$event]} → $event"
    else
        label="(no by-id) → $event"
    fi
    device_list+=("$event")
    echo "$index) $label"
    ((index++))
done

# Step 4: Prompt for selection
read -p "👉 Enter the index of the device you want to select: " selected_index

if [[ ! "$selected_index" =~ ^[0-9]+$ ]] || [[ "$selected_index" -ge "${#device_list[@]}" ]] || [[ "$selected_index" -lt 0 ]]; then
    echo "❌ Invalid index. Please select a number between 0 and $((${#device_list[@]} - 1))."
    exit 1
fi

selected_event="${device_list[$selected_index]}"
echo "🟢 You selected: /dev/input/$selected_event"

# Step 5: Update main.cpp
target_file="main.cpp"
if [ ! -f "$target_file" ]; then
    echo "❌ File $target_file does not exist."
    exit 1
fi

sed -i "s|/dev/input/event[0-9]*|/dev/input/$selected_event|" "$target_file"
echo "✅ Device string in $target_file has been updated to /dev/input/$selected_event"

# Step 6: Build or run the project
echo -e "\n🚀 Step 6: Run the project if already built, otherwise build and run..."

executable="/home/nirantar/Downloads/TUI/examples/build/a.out"

# if [ -f "$executable" ]; then
#     echo "🟢 Executable found. Running it now..."
#     "$executable"
# else 
    echo "🔧 Building the project..."

    project_dir="/home/nirantar/Downloads/TUI/examples"
    build_dir="$project_dir/build"

    cd "$project_dir" || { echo "❌ Failed to enter project directory."; exit 1; }

    echo "📦 Running CMake..."
    cmake -B build .

    echo "⚙️  Compiling..."
    cd build || { echo "❌ Build directory not found."; exit 1; }
    make

    echo "🏃 Running compiled application..."
    ./a.out

    echo "✅ Build and execution completed."
fi
