import subprocess
import pytest
import os

def run_parser(full_name, email):
    """Helper function to run the C++ parser with input."""

    # Combine inputs with newlines, as if the user pressed Enter after each
    input_text = f"{full_name}\n{email}\n"

    result = subprocess.run(
        ["./parser_app"],
        input=input_text,
        capture_output=True,
        text=True,
        check=True
    )

    # Parse the output to find the key-value pairs
    output_data = {}
    for line in result.stdout.strip().splitlines():
        if ":" in line:
            key, value = line.split(":", 1)
            output_data[key.strip()] = value.strip()

    return output_data


def test_simple_name_and_email():
    """Tests a standard first and last name."""
    name = "Jane Doe"
    email = "jane.doe@example.com"

    parsed_info = run_parser(name, email)

    assert parsed_info.get("First Name") == "Jane"
    assert parsed_info.get("Last Name") == "Doe"
    assert parsed_info.get("Username") == "jane.doe"


def test_name_with_middle_initial():
    """Tests a name that includes a middle initial."""
    name = "John A. Doe"
    email = "john.doe@uconn.edu"

    parsed_info = run_parser(name, email)

    assert parsed_info.get("First Name") == "John"
    assert parsed_info.get("Last Name") == "Doe"
    assert parsed_info.get("Username") == "john.doe"
