from PIL import Image
import sys
import os

def rgb_to_x86_palette(r, g, b, a):
    """Convert RGBA color to an x86 assembly-friendly indexed color."""
    # Define x86 16-color palette
    palette = {
        (0, 0, 0): 0x00, # Black
        (0, 0, 170): 0x01, # Blue
        (0, 170, 0): 0x02, # Green
        (0, 170, 170): 0x03, # Cyan
        (170, 0, 0): 0x04, # Red
        (170, 0, 170): 0x05, # Magenta
        (170, 85, 0): 0x06, # Brown
        (170, 170, 170): 0x07, # Light gray
        (85, 85, 85): 0x08, # Dark gray
        (85, 85, 255): 0x09, # Light blue
        (85, 255, 85): 0x0A, # Light green
        (85, 255, 255): 0x0B, # Light cyan
        (255, 85, 85): 0x0C, # Light red
        (255, 85, 255): 0x0D, # Light magenta
        (255, 255, 85): 0x0E, # Yellow
        (255, 255, 255): 0x0F, # White
        (246, 197, 131): 0x42, # Light beige
        (222, 131, 65): 0x41, # Dark beige
        (205, 189, 148): 0x1B # Grey
    }
    
    # Treat fully transparent pixels as black
    if a == 0:
        return 0x00
    
    # Find the closest match in the palette
    closest_color = min(palette.keys(), key=lambda c: (c[0] - r) ** 2 + (c[1] - g) ** 2 + (c[2] - b) ** 2)
    return palette[closest_color]

def png_to_asm_variable(image_path, output_file):
    try:
        img = Image.open(image_path).convert("RGBA")
        width, height = img.size
        pixels = list(img.getdata())
        
        asm_code = f"{os.path.basename(image_path).split('.')[0]} db "
        
        for y in range(height):
            row_data = pixels[y * width:(y + 1) * width]
            asm_code += ", ".join(f"0x{rgb_to_x86_palette(r, g, b, a):02X}" for r, g, b, a in row_data)
            if y < height - 1:
                asm_code += "\n       db "
        
        with open(output_file, "w") as f:
            f.write(asm_code)
        
        print(f"Assembly variable written to {output_file}")
        
    except Exception as e:
        print(f"Error processing {image_path}: {e}")
        return None

def process_images_in_folder(folder_path):
    if not os.path.isdir(folder_path):
        print(f"Error: {folder_path} is not a valid directory.")
        return
    
    for filename in os.listdir(folder_path):
        if filename.lower().endswith(".png"):
            image_path = os.path.join(folder_path, filename)
            output_file = os.path.join(folder_path, f"{os.path.splitext(filename)[0]}.inc")
            png_to_asm_variable(image_path, output_file)

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python script.py <directory>")
        sys.exit(1)
    
    directory_path = sys.argv[1]
    process_images_in_folder(directory_path)
