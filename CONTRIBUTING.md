# CONTRIBUTING

#### The libkc_datastructs project welcomes new contributors. This document will guide you through the process.

## Fork

Fork the project on [GitHub](https://github.com/Daniel-Tanase/libkc_datastructs)
and check out your copy.

```
$ git clone https://github.com/[your-username]/libkc_datastructs.git
$ cd libkc_datastructs
$ git remote add upstream https://github.com/Daniel-Tanase/libkc_datastructs.git
```

## Branch

Okay, so you cloned the repository. Create a feature branch and start hacking.
The branch name should follow the following pattern (see also examples on GitHub):

`<name initials>/<branch name>`

Use suggestive branch names and use no more than 3 words separated by - (hyphen).

Full example:

`$ git checkout -b kc/my-feature-branch -t origin/master`

## Code

Please adhere to libkc_datastructs's code style. In general it follows the
conventions from the [Google C/C++](https://google.github.io/styleguide/cppguide.html)
style guide. Some of the key points, as well as some additional guidelines, are
enumerated below.

- Names should be descriptive and concise.

- Use two spaces and no tabs.

- Lines should be wrapped at 80 characters.

- Ensure that lines have no trailing whitespace.

- Use C99-compliant syntax.

- When writing comments, use properly constructed sentences, including punctuation.

- When documenting APIs and/or source code, don't make assumptions or make
implications about race, gender, religion, political orientation or anything
else that isn't relevant to the project.

- Remember that source code usually gets written once and read often: ensure the
reader doesn't have to make guesses. Make sure that the purpose and inner logic
are either obvious to a reasonably skilled professional, or add a comment that
explains it.

## Commit

Make sure git knows your name and email address:

```
$ git config --global user.name "J. Random User"
$ git config --global user.email "j.random.user@example.com"
```

Writing good commit logs is important. A commit log should describe what changed
and why. Follow these guidelines when writing one:

1. The first line should be 50 characters or less and contain a short description
of the change prefixed with the name of the changed subsystem
(e.g. `feat: implemented seach() function for set`).

2. Keep the second line blank.

3. Wrap all other lines at 72 columns.

A good commit log looks like this:

```
subsystem: explaining the commit in one line

Body of commit message is a few lines of text, explaining things
in more detail, possibly giving some background about the issue
being fixed, etc etc.

The body of the commit message can be several paragraphs, and
please do proper word-wrap and keep columns shorter than about
72 characters or so. That way `git log` will show things
nicely even when it is indented.
```

The header line should be meaningful; it is what other people see when they run
`git shortlog` or `git log --oneline`.

Check the output of `git log --oneline files_that_you_changed` to find out what
subsystem (or subsystems) your changes touch.

## Rebase

Use `git rebase` (not `git merge`) to sync your work from time to time.

```
$ git fetch upstream
$ git rebase upstream/master
```

## Tests

Bug fixes and features should come with tests. Add your tests in the `tests/`
directory.

Look at other tests to see how they should be structured (license boilerplate,
the way entry points are declared, etc.).

Check README.md file to find out how to run the test suite and make sure that
there are no test regressions.

## Push

```
$ git push origin kc/my-feature-branch
```

Go to `https://github.com/[your-username]/libkc_datastructs` and select your
feature branch. Click the 'Pull Request' button and fill out the form.

Pull requests are usually reviewed within a few days. If there are comments to
address, apply your changes in a separate commit and push that to your feature
branch. Post a comment in the pull request afterwards; GitHub does not send out
notifications when you add commits.
