import subprocess, pathlib

ROOT = pathlib.Path(__file__).resolve().parent
BUILD = ROOT / "build"
BIN = BUILD / "logger"

def run(bin_path, args=(), stdin_data=""):
    proc = subprocess.run([str(bin_path), *map(str,args)],
                          input=stdin_data.encode(),
                          stdout=subprocess.PIPE,
                          stderr=subprocess.STDOUT,
                          check=False)
    return proc.returncode, proc.stdout.decode()

# ---------- Basic startup/args ----------

def test_usage_message_no_args():

    code, out = run(BIN, args=())
    assert "Usage: ./logger <capacity>" in out
    assert code == 1

def test_capacity_must_be_positive():

    code, out = run(BIN, args=(0,))
    assert "Capacity must be > 0" in out
    assert code == 1

# ---------- Adding and printing ----------

def test_add_single_reading_then_print():

    input_seq = (
        "1\n"
        "A 1.2\n"
        "3\n"
        "5\n"
    )
    code, out = run(BIN, args=(3,), stdin_data=input_seq)
    assert "A: 1.2" in out

def test_add_two_readings_then_print():

    input_seq = (
        "1\n"
        "A 1.2\n"
        "1\n"
        "B 3.8\n"
        "3\n"
        "5\n"
    )
    code, out = run(BIN, args=(4,), stdin_data=input_seq)
    assert "A: 1.2" in out
    assert "B: 3.8" in out

# ---------- Update via pointer ----------

def test_update_value_by_index():

    input_seq = (
        "1\n"
        "A 4.4\n"
        "2\n"
        "0 9.5\n"
        "3\n"
        "5\n"
    )
    code, out = run(BIN, args=(2,), stdin_data=input_seq)
    assert "A: 9.5" in out

def test_update_bad_index_reports_error():

    input_seq = (
        "1\n"
        "A 4.4\n"
        "2\n"
        "5 1.0\n"
        "5\n"
    )
    code, out = run(BIN, args=(2,), stdin_data=input_seq)
    assert "Error: Bad index" in out

# ---------- Aggregates (avg/min/max) ----------

def test_compute_average_only():

    input_seq = (
        "1\n"
        "A 1.2\n"
        "1\n"
        "B 3.8\n"
        "4\n"
        "1\n"
        "5\n"
    )
    code, out = run(BIN, args=(5,), stdin_data=input_seq)
    assert "result=2.5" in out
    assert "rounded=2" in out

def test_compute_min_only():

    input_seq = (
        "1\n"
        "A 1.2\n"
        "1\n"
        "B 3.8\n"
        "4\n"
        "2\n"
        "5\n"
    )
    code, out = run(BIN, args=(5,), stdin_data=input_seq)
    assert "result=1.2" in out

def test_compute_max_only():

    input_seq = (
        "1\n"
        "A 1.2\n"
        "1\n"
        "B 3.8\n"
        "4\n"
        "3\n"
        "5\n"
    )
    code, out = run(BIN, args=(5,), stdin_data=input_seq)
    assert "result=3.8" in out

# ---------- Capacity and empty errors ----------

def test_insert_when_full_reports_error():

    input_seq = (
        "1\n"
        "A 1\n"
        "1\n"
        "B 2\n"
        "1\n"
        "C 3\n"
        "5\n"
    )
    code, out = run(BIN, args=(2,), stdin_data=input_seq)
    assert "Error: Full" in out

def test_average_on_empty_reports_error():

    input_seq = (
        "4\n"
        "1\n"
        "5\n"
    )
    code, out = run(BIN, args=(3,), stdin_data=input_seq)
    assert "Error: Empty" in out

def test_min_on_empty_reports_error():

    input_seq = (
        "4\n"
        "2\n"
        "5\n"
    )
    code, out = run(BIN, args=(3,), stdin_data=input_seq)
    assert "Error: Empty" in out

def test_max_on_empty_reports_error():

    input_seq = (
        "4\n"
        "3\n"
        "5\n"
    )
    code, out = run(BIN, args=(3,), stdin_data=input_seq)
    assert "Error: Empty" in out

# ---------- Unknown selections ----------

def test_unknown_menu_choice_prints_message():

    input_seq = (
        "7\n"
        "5\n"
    )
    code, out = run(BIN, args=(1,), stdin_data=input_seq)
    assert "Unknown choice" in out

def test_unknown_compute_option_prints_message():

    input_seq = (
        "4\n"
        "9\n"
        "5\n"
    )
    code, out = run(BIN, args=(1,), stdin_data=input_seq)
    assert "Unknown op" in out
