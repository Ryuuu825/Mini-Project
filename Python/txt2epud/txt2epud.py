import os
import sys
import re
import argparse
import chinese_converter
import subprocess

def create＿xhtml(book_title, chp_content):

    # convert chp_content to string
    chp_content = '\n'.join(chp_content)

    chp_content = chp_content \
        .replace("    ", "\n") \
        .replace("&", "&amp;") \
        .replace(' ', '&nbsp;') \
        .replace('\t', '&nbsp;&nbsp;&nbsp;&nbsp;') \
        .replace('\r', '') \
        .replace('<', '&lt;') \
        .replace('>', '&gt;') \
        .replace('\n', '<br />\n') 

    chp_content = chinese_converter.to_traditional(chp_content)


    template = \
        """<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN" "http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="zh-TW">
    <head>
        <title>{book_title}</title>
        <link href="stylesheet.css" type="text/css" rel="stylesheet" />
        <link
            rel="stylesheet"
            type="application/vnd.adobe-page-template+xml"
            href="page-template.xpgt"
        />
    </head>
    <body>
        <div>
            <h3>{book_title}</h3>
            {chp_content}
        </div>
    </body>
</html>"""

    return template.format(book_title=book_title, chp_content=chp_content)


def create_content＿opf(book_title, chapters):
    author = 'KEN'

    counter = 0
    items_string = ''
    items_ref_string = ''
    for _ in chapters:
        items_string += """<item id="P{id}" href="{id}.xhtml" media-type="application/xhtml+xml" />\n""".format(
            id=counter)
        items_ref_string += """<itemref idref="P{id}" />\n""".format(id=counter)
        counter += 1

    template = \
        """<?xml version="1.0"?>
<package version="2.0" xmlns="http://www.idpf.org/2007/opf" unique-identifier="BookId">
 <metadata xmlns:dc="http://purl.org/dc/elements/1.1/" xmlns:opf="http://www.idpf.org/2007/opf">
   <dc:creator opf:role="aut">{author}</dc:creator>
   <dc:title>{book_title}</dc:title>
   <dc:language>zh-TW</dc:language>
   <dc:identifier id="BookId">www.haodoo.net</dc:identifier>
 </metadata>
 <manifest>
  <item id="ncx" href="toc.ncx" media-type="application/x-dtbncx+xml" />
  <item id="style" href="stylesheet.css" media-type="text/css" />
  <item id="pagetemplate" href="page-template.xpgt" media-type="application/vnd.adobe-page-template+xml" />
    {items_string}
 </manifest>
<spine toc="ncx">
    {items_ref_string}
 </spine>
</package>
"""
    return template.format(author=author, book_title=book_title, items_string=items_string, items_ref_string=items_ref_string)


def create_page_template_xpgt():
    return """<ade:template xmlns="http://www.w3.org/1999/xhtml" xmlns:ade="http://ns.adobe.com/2006/ade"
		 xmlns:fo="http://www.w3.org/1999/XSL/Format">

  <fo:layout-master-set>
   <fo:simple-page-master master-name="single_column">
		<fo:region-body margin-bottom="3pt" margin-top="0.5em" margin-left="3pt" margin-right="3pt"/>
    </fo:simple-page-master>
  
    <fo:simple-page-master master-name="single_column_head">
		<fo:region-before extent="8.3em"/>
		<fo:region-body margin-bottom="3pt" margin-top="6em" margin-left="3pt" margin-right="3pt"/>
    </fo:simple-page-master>

    <fo:simple-page-master master-name="two_column"	margin-bottom="0.5em" margin-top="0.5em" margin-left="0.5em" margin-right="0.5em">
		<fo:region-body column-count="2" column-gap="10pt"/>
    </fo:simple-page-master>

    <fo:simple-page-master master-name="two_column_head" margin-bottom="0.5em" margin-left="0.5em" margin-right="0.5em">
		<fo:region-before extent="8.3em"/>
		<fo:region-body column-count="2" margin-top="6em" column-gap="10pt"/>
    </fo:simple-page-master>

    <fo:simple-page-master master-name="three_column" margin-bottom="0.5em" margin-top="0.5em" margin-left="0.5em" margin-right="0.5em">
		<fo:region-body column-count="3" column-gap="10pt"/>
    </fo:simple-page-master>

    <fo:simple-page-master master-name="three_column_head" margin-bottom="0.5em" margin-top="0.5em" margin-left="0.5em" margin-right="0.5em">
		<fo:region-before extent="8.3em"/>
		<fo:region-body column-count="3" margin-top="6em" column-gap="10pt"/>
    </fo:simple-page-master>

    <fo:page-sequence-master>
        <fo:repeatable-page-master-alternatives>
            <fo:conditional-page-master-reference master-reference="three_column_head" page-position="first" ade:min-page-width="80em"/>
            <fo:conditional-page-master-reference master-reference="three_column" ade:min-page-width="80em"/>
            <fo:conditional-page-master-reference master-reference="two_column_head" page-position="first" ade:min-page-width="50em"/>
            <fo:conditional-page-master-reference master-reference="two_column" ade:min-page-width="50em"/>
            <fo:conditional-page-master-reference master-reference="single_column_head" page-position="first" />
            <fo:conditional-page-master-reference master-reference="single_column"/>
        </fo:repeatable-page-master-alternatives>
    </fo:page-sequence-master>

  </fo:layout-master-set>

  <ade:style>
    <ade:styling-rule selector=".title_box" display="adobe-other-region" adobe-region="xsl-region-before"/>
  </ade:style>

</ade:template>
"""


def create_stylesheet_css():
    return """

@font-face {
   font-family: "DroidFont", serif, sans-serif;
   src: url(res:///system/fonts/DroidSansFallback.ttf);
}

body { margin-left: 5%; margin-right: 5%; margin-top: 5%; margin-bottom: 5%; text-align: justify;}

h1 { text-align: center; }
h2 { text-align: center; }
h3 { text-align: center; }
h4 { text-align: center; }
h5 { text-align: center; }
h6 { text-align: center; }
.CI {
    text-align:center;
    margin-top:0px;
    margin-bottom:0px;
    padding:0px;
}
.center   {text-align: center;}
.smcap    {font-variant: small-caps;}
.u        {text-decoration: underline;}
.bold     {font-weight: bold;}
"""


def create_toc_ncx(book_title, chapters):
    nav_points_template_string =  \
    """<navPoint id="P{id}" playOrder="{id}">
      <navLabel>
        <text>{name}</text>
      </navLabel>
      <content src="{id}.xhtml"/>
    </navPoint>
    """

    nav_points_string = ""

    counter = 0

    for chp_name in chapters:
        # remove the entity reference
        chp_name = re.sub(r"&\w+;", "", chp_name)

        nav_points_string += nav_points_template_string.format(id=counter, name=chp_name)
        counter += 1

    template = """<?xml version="1.0" encoding="UTF-8"?>
<ncx xmlns="http://www.daisy.org/z3986/2005/ncx/" version="2005-1" xml:lang="zh-TW">
  <head>
    <meta name="dtb:uid" content="www.haodoo.net"/>
    <meta name="dtb:depth" content="1"/>
    <meta name="dtb:totalPageCount" content="0"/>
    <meta name="dtb:maxPageNumber" content="0"/>
  </head>
  <docTitle>
    <text> {book_title} </text>
  </docTitle>
  <navMap>
    {nav_points_string}
  </navMap>
</ncx>
"""
    return template.format(book_title=book_title, nav_points_string=nav_points_string)


def main():

    parser = argparse.ArgumentParser(description='Convert txt file downloaded from www.wenku8.net to epub file')
    parser.add_argument('filename', help='the txt file to convert')
    parser.add_argument('-o', '--output', help='the output file name' , default="output.epub")
    args = parser.parse_args()

    filename = args.filename
    if not os.path.exists(filename):
        print('File not found: %s' % filename)
        sys.exit(1)

    print("[Reading file]: %s" % filename )
    with open(filename, 'r', encoding='utf-8') as f:
        content = f.read()

    print("[Processing file] " )

    # remove the first line
    content = re.sub(r'^.*\r? *', '', content)

    # remove the last line
    content = re.sub(r'\r? *$', '', content)

    # The thrid line is the book title
    lines = content.splitlines()
    book_tile = chinese_converter.to_traditional(lines[2].replace("<", "").replace(">", ""))

    chapters = {}
    current_chapter = None

    for line in lines:
        if re.match(r'^第.*卷', line):
            line = chinese_converter.to_traditional(line)
            chapters[line] = []
            current_chapter = line
            continue

        # if the line is tabbed / four spaces, add to the last chapter
        if line.startswith(' ' * 4) or line.startswith('\t'):
            chapters[current_chapter].append(line)
            continue

        # if the line is empty, skip it
        if not line:
            continue

    # create OEBPS directory
    if not os.path.exists('OEBPS'):
        os.mkdir('OEBPS')

    counter = 0
    for key, value in chapters.items():
        chapters[key] = create_xhtml(key, value)
        # create the file
        with open("OEBPS/" + str(counter) + '.xhtml', 'w', encoding='utf-8') as f:
            f.write(chapters[key])
        counter += 1

    # create the content.opf file
    with open('OEBPS/content.opf', 'w', encoding='utf-8') as f:
        f.write(create_content＿opf(book_title=book_tile, chapters=chapters))

    # create the page-template.xpgt file
    with open('OEBPS/page-template.xpgt', 'w', encoding='utf-8') as f:
        f.write(create_page_template_xpgt())

    # create the stylesheet.css file
    with open('OEBPS/stylesheet.css', 'w', encoding='utf-8') as f:
        f.write(create_stylesheet_css())

    # create the toc.ncx file
    with open('OEBPS/toc.ncx', 'w', encoding='utf-8') as f:
        f.write(create_toc_ncx(book_title=book_tile, chapters=chapters))

    # create mine type file
    with open('mimetype', 'w', encoding='utf-8') as f:
        f.write('application/epub+zip')
    
    # create META-INF directory
    if not os.path.exists('META-INF'):
        os.mkdir('META-INF')

    # create container.xml file
    with open('META-INF/container.xml', 'w', encoding='utf-8') as f:
        f.write("""<?xml version="1.0"?>
<container version="1.0" xmlns="urn:oasis:names:tc:opendocument:xmlns:container">
  <rootfiles>
    <rootfile full-path="OEBPS/content.opf" media-type="application/oebps-package+xml"/>
  </rootfiles>
</container>""")

    print("[File processed] "  )

    # check if output file name include / 
    real_file_name = args.output.replace('.epub', '')

    print("[Writing to epub file]: %s.epub" % args.output )

    if args.output and (args.output.find('/') != -1 ) and not os.path.exists(args.output.split('/')[0]):
        os.mkdir(args.output.split('/')[0])

    # disable stdout from os.system
    # 'zip -X0 "%s.epub" mimetype' % real_file_name
    os.system('zip -X0 "%s.epub" mimetype > /dev/null' % real_file_name)
    # 'zip -Xur9D "%s.epub" META-INF/* OEBPS/*' % real_file_name
    os.system('zip -Xur9D "%s.epub" META-INF/* OEBPS/* > /dev/null' % real_file_name)
    print("[File written] "  )
    print("[Cleaning up]")
    # 'rm -rf META-INF OEBPS mimetype'
    subprocess.run(['rm', '-rf', 'META-INF', 'OEBPS', 'mimetype'], stdout=subprocess.DEVNULL)

if __name__ == '__main__': 
    main()
