# Lab 2 — Linux Navigation and File Management: individual report

- Student name/ID: THA WINNER / e20230181
- Ubuntu username: gic-tha-winner
- My values (`oslab values lab2`): file1 = sales north.txt, file2 = audit notes.txt, owner = Legal, reader = Support, third = HR
- Files: `evidence/paths.txt`, `evidence/tree.txt`, `evidence/checkpoint.txt`

## What I Did

| Step | My command | Current folder when I ran it |
|---|---|---|
| Move the first file (relative destination) | `mv -- "$file1" ../reports/` | `lab2/incoming` |
| Move the second file (absolute paths) | `mv -- "$OSLAB_WORKSPACE/lab2/incoming/$file2" "$OSLAB_WORKSPACE/lab2/reports/"` | `oslab-work` (by mistake, one level too high, but it still worked because both paths were absolute) |
| Read the report from my reader department (relative path) | `cat "../Legal/sales north.txt"` | `lab2/TechCorp/Support` |
| The path error I made on purpose, and its message | `cat "reports/sales north.txt"` gave `cat: 'reports/sales north.txt': No such file or directory` | `lab2/TechCorp/Support` |
| The relative path that fixed it | `../../reports/sales north.txt` | `lab2/TechCorp/Support` |

## Explanation

A correct file name can still give "No such file or directory" when the path is relative and I run the command from the wrong folder. A relative path starts from the folder I am in (`pwd`), so `reports/sales north.txt` only works from `lab2`. From `TechCorp/Support` there is no `reports` folder, so I needed `../../` to go up two levels first. A missing pair of quotes can also cause it: without quotes, `sales north.txt` is split into two names. `mv` moved my files out of `incoming/`, so `incoming/` became empty, but `cp` copied them into `TechCorp/Legal/`, so the originals stayed in `reports/`.

## What My Tests Do Not Prove

`ls` only shows that a file with that name exists, not what is inside it. `cmp` proves that the copies in `TechCorp/Legal/` had exactly the same bytes as the files in `reports/` when I ran it, but it does not prove that they are the right reports or that nobody changes them later.

## Plus / Challenge (only if you did them)

Not done.

## AI Note (optional)

An AI tool suggested that `oslab check` showed TRY for "records a relative and an absolute path" because my `paths.txt` only had commands with variables like `$OSLAB_WORKSPACE`, not real paths. It suggested adding the same commands with the real paths written out. I tested it by running `oslab check lab2` again, and that milestone changed to PASS.
