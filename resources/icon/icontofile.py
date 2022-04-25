import sys
from PIL import Image
image = Image.open(sys.argv[1])

gpl = """/**
 * Powder Toy - Main source
 *
 * Copyright (c) 2008 - 2010 Stanislaw Skowronek.
 * Copyright (c) 2010 Simon Robertshaw
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02111-1301  USA
 */
"""

output = ""
formatted = []
for pixel in image.getdata():
    formatted.extend("0x{0:02X}".format(byte) for byte in pixel)

with open('../../data/icon.cpp', 'w') as f:
    f.write(gpl)
    f.write('extern const unsigned char app_icon[] = {\n')
    limit = len(formatted)//16

    for i in range(limit + 1):
        end = "};" if i == limit else ',\n'
        f.write(", ".join(formatted[i*16:(i+1)*16]) + end)


"""with open(sys.argv[1], "rb") as icon:
	icondata = icon.read()
output = ["0x{0:02X}".format(ord(byte)) for byte in icondata]
for line in range(len(output)/16+1):
	print(", ".join(output[line*16:(line+1)*16])+",")"""
