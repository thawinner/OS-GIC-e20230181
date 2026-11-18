# Lab 4 — Redirection and Pipelines: individual report

- Name / student ID: THA WINNER/ e20230181
- Linux account: gic-tha-winner
- Personal status and other word: status = `done`, other = `paid`

## Commands I Used

My actual commands are saved one per line in `evidence/commands.txt` (10 lines). It is a plain-text record, not a script.

| Stage | My command | Input received | Output produced |
|---|---|---|---|
| Select exact first field | `grep '^done,' data/events.csv \| tee evidence/selected.txt` | `data/events.csv`: 1 header line + 6 records | 3 full rows `done,4`, shown on screen and saved in `selected.txt` (`done-late,89` is not selected) |
| Extract field 2 | `grep '^done,' data/events.csv \| cut -d, -f2 \| tee evidence/fields.txt` | `cut` receives the 3 selected rows from `grep` | 3 quantities `4`, `4`, `4` in `fields.txt` |
| Count selected records | `grep '^done,' data/events.csv \| wc -l > evidence/normal.txt` | `wc -l` receives the 3 selected rows from `grep` | `3` in `normal.txt`; `diff -u data/expected.txt evidence/normal.txt` printed nothing, so the count is correct |
| Save stdout and stderr separately | `cat data/missing.csv > evidence/stdout.txt 2> evidence/stderr.txt` | the name of a file that does not exist | `stdout.txt` is empty (0 bytes); `stderr.txt` has `cat: data/missing.csv: No such file or directory` |
| Save exit status immediately | `echo $? > evidence/status.txt` | the exit status of the `cat` command just before | `1` in `status.txt` (nonzero = failure) |

## What My Tests Show

| Test | Expected | Observed | Mistake it would catch |
|---|---|---|---|
| Original records | 3 exact matches | `3` in `normal.txt`; 3 rows `done,4` in `selected.txt`; `done-late,89` not selected | Prefix matching: `grep '^done'` without the comma would also select `done-late,89` and give 4. Counting quantities: a sum would give 4+4+4 = 12, not 3. |
| No match | 0 records | `0` (first line of `edge.txt`), from `data/no-match.csv` with only `paid,2` | A pattern that matches the wrong word or the header. It also shows that "no matching record" gives 0 and is not the same as "file missing". |
| One added match plus a look-alike | 4 records | `4` (second line of `edge.txt`), from `data/changed.csv` with `done,7` and `done-late,99` added | Prefix matching: `done-late,99` would make it 5. Counting quantities: `done,7` adds one record, not 7. Discarding earlier results with `>`: I used `>>`, so `edge.txt` kept both `0` and `4`; with `>` the `0` would be lost. |
| Missing input | empty stdout, diagnostic on stderr, nonzero status | `stdout.txt` empty (0 bytes), `stderr.txt` has the `missing.csv` message, `status.txt` = `1` | Mixing up stdout and stderr, or thinking a command worked because no normal output appeared. |

`oslab check lab4` showed `milestones: 5/5` (4 Core milestones + checkpoint).

### Live checkpoint

Fresh input `data/river.csv` with my status `done`:

```text
grep '^done,' data/river.csv | tee evidence/checkpoint-selected.txt
grep '^done,' data/river.csv | wc -l > checkpoint.txt
```

`checkpoint-selected.txt` has `done,14` and `done,10`. `checkpoint.txt` has `2`. `done-late,72` and `not-done,56` were not selected. The record count is 2, but the sum of quantities would be 14 + 10 = 24.

## Explain the Commands

1. **Why does the comma in `grep '^done,'` matter?**
   The comma ends the first field. So `grep` only selects lines where the first field is exactly `done`. Without the comma, `done-late,89` would also match, because it also starts with `done`. The `^` makes the match start at the beginning of the line, so `not-done,56` does not match.

2. **Why does `wc -l` count records here, rather than add quantities?**
   `wc -l` counts the lines it receives. Each selected line is one record, so it gives 3. It does not read the numbers inside the lines. Adding the quantities (field 2) is a different question: it gives 4+4+4 = 12.

3. **Where did you use `>>`, and what would `>` do instead?**
   I used `>>` for the second count in `edge.txt` (`grep '^done,' data/changed.csv | wc -l >> evidence/edge.txt`) and in the Guided part (`second observation`). `>>` adds to the end of the file and keeps the old lines. `>` would replace the file, so the first result (`0`) would be lost.

4. **What does `tee` do that `>` alone does not?**
   `tee` shows the output on the screen and saves it in a file at the same time. `>` only saves it in the file, and nothing appears on the screen. `tee -a` also keeps the old file content.

5. **Why must `echo $?` immediately follow the command being checked?**
   `$?` holds the exit status of only the last command. If I run another command first (for example `cat evidence/stdout.txt`), `$?` changes to the status of that new command, and I lose the status of the command I wanted to check.

6. **Why can `cat missing-file | wc -l` report pipeline status 0?**
   A pipeline reports the status of its last command. `cat` failed and printed the error on stderr (stderr does not go through the pipe). But `wc -l` received empty input, printed `0` and finished successfully, so the pipeline status is 0. A successful last stage does not prove that the input was read.

## Limits and Evidence

These commands assume simple comma-separated text without quoted commas. Saved results describe one run; they do not prove every future input works or who typed a command.

Submitted files: `README.md`, `checkpoint.txt`, and in `evidence/`: `commands.txt`, `selected.txt`, `fields.txt`, `normal.txt`, `edge.txt`, `stdout.txt` (empty on purpose), `stderr.txt`, `status.txt`, `checkpoint-selected.txt`. Extra practice files from the Guided part are also included: `practice.txt`, `tee-demo.txt`, `demo-out.txt` (empty on purpose), `demo-error.txt`, `both.txt`. No `report.sh`.

## Optional Work / AI Note

