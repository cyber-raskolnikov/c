#!/bin/bash

# Check if the correct number of arguments is provided
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <project_name>; where project_name is single word"
    exit 1
fi

# Get the project name from the first argument
PROJECT_NAME=$1

# Create a new directory with the project name
mkdir -p "projects/$PROJECT_NAME"

# Check if the layouts directory exists
if [ ! -d "layouts" ]; then
    echo "Error: 'layouts' directory does not exist."
    exit 1
fi

# Copy files from the layouts directory to the new project directory
cp layouts/helloworld.c "projects/$PROJECT_NAME/$PROJECT_NAME.c"
cp layouts/Makefile "projects/$PROJECT_NAME/Makefile"

# Replace 'XXX' with the project name in the copied files
for FILE in "projects/$PROJECT_NAME"/*; do
    if [ -f "$FILE" ]; then
        # the empty string '' is necessary in OSX (https://stackoverflow.com/questions/39325759/sed-on-mac-extra-characters-after-p-command)
        # replacing the PLACEHOLDER string in the layout files for the provided project name
        sed -i '' "s/PLACEHOLDER/$PROJECT_NAME/g" "$FILE"
    fi
done

echo "Project setup complete. Files copied and placeholders replaced."
