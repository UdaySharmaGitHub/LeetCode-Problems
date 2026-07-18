#!/bin/bash

# Setup Git Hooks for GFG-Problems Repository
# This script copies the shared hooks from git_hooks/ to .git/hooks/
# and makes them executable

echo "🔧 Setting up Git Hooks..."

# Check if git_hooks directory exists
if [ ! -d "git_hooks" ]; then
    echo "❌ Error: git_hooks directory not found!"
    echo "Make sure you're in the root of the GFG-Problems repository"
    exit 1
fi

# Copy hooks to .git/hooks/
mkdir -p .git/hooks

cp git_hooks/prepare-commit-msg .git/hooks/prepare-commit-msg
cp git_hooks/commit-msg .git/hooks/commit-msg

# Make hooks executable
chmod +x .git/hooks/prepare-commit-msg
chmod +x .git/hooks/commit-msg

echo "✅ Git hooks installed successfully!"
echo ""
echo "📝 Hook Details:"
echo "   • prepare-commit-msg: Auto-generates commit messages"
echo "     Format: POTD DD-MM-YYYY : problem_name"
echo ""
echo "   • commit-msg: Validates commit message format"
echo "     Ensures messages are at least 5 characters"
echo ""
echo "🎯 Try it out: git commit (message will be auto-generated)"
echo ""
