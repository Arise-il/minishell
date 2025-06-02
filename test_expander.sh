#!/bin/bash

# Set up test environment
export USER="oouhlale"
export HOME="/home/oouhlale"
export VAR_123="works"
export SPECIAL="Hello!"
unset UNSET_VAR
LAST_EXIT=42

# Simulate $? behavior (manually pass it if needed)
last_exit() {
	echo "$LAST_EXIT"
}

# Tests to run
tests=(
	'echo $USER'
	'echo $HOME'
	'echo $HOME$USER'
	'echo HELLO$USER'
	'echo "$USER"'
	"echo '\$USER'"
	'echo "$HOME$USER"'
	"echo '\$HOME\$USER'"
	'echo "$USER "TEST'
	'echo "$USER""TEST"'
	'echo prefix$USERsuffix'
	'echo $UNSET_VAR'
	'echo $?'
	'echo "$?$USER"'
	'echo $'
	'echo abc$'
	'echo $VAR_123'
	'echo $USER $HOME $?'
	'echo $SPECIAL?'
	'echo "$USER TEST OK"'
	'echo $USER TEST OK'
)

echo "---------- EXPANDER TEST ----------"
for test in "${tests[@]}"; do
	echo -e "\nTest: $test"
	echo "Your Minishell output:"
	# Replace this with your minishell run:
	echo "$test" | ./minishell

	echo "Expected Bash output:"
	# Simulate $? by replacing $? with fixed $LAST_EXIT
	eval "$(echo "$test" | sed "s/\\$?/$LAST_EXIT/g")"
done

