Moredown - Discount Markdown Processor for Ruby (with some extras)
==================================================================

Discount is an implementation of John Gruber's Markdown markup language in C. It
implements all of the language described in [the markdown syntax document][1] and
passes the [Markdown 1.0 test suite][2].

Discount was developed by [David Loren Parsons][3]. The Ruby extension was
developed by [Ryan Tomayko][4] and extended by [Nathan Hoad][5].

[1]: http://daringfireball.net/projects/markdown/syntax
[2]: http://daringfireball.net/projects/downloads/MarkdownTest_1.0.zip
[3]: http://www.pell.portland.or.us/~orc
[4]: http://tomayko.com/
[5]: http://nathanhoad.net/

Installation, Hacking
---------------------

The Moredown gem can be installed from [Rubygems](https://rubygems.org/gems/moredown):

    $ gem install moredown

The Moredown sources are available via Git:

    $ git clone git://github.com/nathanhoad/moredown.git
    $ cd moredown
    $ rake --tasks

For more information, see [the project page](http://github.com/nathanhoad/moredown).

Usage
-----

Moredown can be used in any way that RDiscount can be (see below). In addition, Moredown
implements some extras:

 * Static method for simple calls

        require 'moredown'
        html = Moredown.text_to_html("Hello World!")

 * Remap relative URLs

        Moredown.new(text, :base_url => 'http://nathanhoad.net').to_html

 * Remap headings (eg. h1 becomes h3).

        Moredown.new(text, :map_headings => 2)

 * Embed Youtube videos (similar to image syntax except the title text is used for width and height)

        ![Video](youtube:lfAzVe5H-vE)
        ![Blah](youtube:lfAzVe5H-vE "400 300")

 * Use Flash movies (include the width and height if you want)

        ![Flash](flash:movieclip.swf)
        ![Something](flash:something.swf "200 100")

 * Use SwfObject (javascript not included) for graceful Flash degradation

        Moredown.new(text, :swfobject => { :src => 'swfobject.js', :version => '10', :fallback => 'No Flash' })

 * Image alignments (extension to image syntax)

        ![Image](/images/test.jpg):left
        ![Image](/images/test.jpg):right
        ![Image](/images/test.jpg):center

 * Emoticons

        :-)
        :-P
        :-D
        :-(
        :-@
        ;-)

 * RDiscount extensions are now passed under `:extensions`

        Moredown.new(text, :extensions => [:smart])

RDiscount implements the basic protocol popularized by RedCloth and adopted
by BlueCloth:

    require 'moredown'
    markdown = Moredown.new("Hello World!")
    puts markdown.to_html

Inject Moredown into your BlueCloth-using code by replacing your bluecloth
require statements with the following:

    begin
      require 'moredown'
      BlueCloth = Moredown
    rescue LoadError
      require 'bluecloth'
    end


COPYING
-------

Discount is free software;  it is released under a BSD-style license
that allows you to do as you wish with it as long as you don't attempt
to claim it as your own work. RDiscount adopts Discount's license
verbatim. See the file `COPYING` for more information.
