import gi
import csv

gi.require_version('Gtk', '4.0')
from gi.repository import Gtk, Gio, GObject, GdkPixbuf

APPID = 'com.example.liststore'


class Row(GObject.Object):
    def __init__(self, *data):
        super().__init__()
        self.data = data


class Gtk4TestTest(Gtk.ApplicationWindow):
    def __init__(self, app):
        super().__init__(application=app, title='Visualización Alineación')

        # Establecer tamaño de la ventana
        #self.set_default_size(1000, 600)

        # Leer matriz desde archivo CSV
        self.matriz = self.leer_csv('matriz_gtk.csv')

        if not self.matriz:
            print("El archivo CSV está vacío o no se pudo leer.")
            self.matriz = [["No hay datos"]]  # Valor por defecto en caso de error

        # Agregar nombres a las filas como primera columna
        self.matriz = [[f"Fila {i + 1}"] + fila for i, fila in enumerate(self.matriz)]

        # Crear el contenedor principal
        vbox = Gtk.Box(orientation=Gtk.Orientation.VERTICAL, spacing=10)
        self.set_child(vbox)


        # self.image_box = Gtk.Box(orientation=Gtk.Orientation.HORIZONTAL, spacing=10)
        # self.image_box.set_hexpand(True)
        # self.image_box.set_vexpand(True)
        # vbox.append(self.image_box)
        
        # # Agregar imagen al contenedor
        # self.imagen = Gtk.Image()
        # self.cargar_imagen("archivo.png")
        # self.image_box.append(self.imagen)
        
        # Crear ColumnView para mostrar la matriz
        self.columnview = Gtk.ColumnView()
        vbox.append(self.columnview)

        # Crear modelo para los datos
        self.model = Gio.ListStore()
        for fila in self.matriz:
            self.model.append(Row(*fila))

        # Configurar datos en ColumnView
        smodel = Gtk.SingleSelection(model=self.model)
        self.columnview.set_model(smodel)
        self.crear_columnas(len(self.matriz[0]))


        self.button = Gtk.Button(label="Mostrar Alineamiento")
        self.button.connect("clicked", self.on_button_clicked)
        vbox.append(self.button)

        #self.connect("notify::size", self.on_window_resize)

    def cargar_imagen(self, image_path):
        pixbuf = GdkPixbuf.Pixbuf.new_from_file(image_path)
        scaled_pixbuf = pixbuf.scale_simple(2000, 2000, GdkPixbuf.InterpType.BILINEAR)
        self.imagen.set_from_pixbuf(scaled_pixbuf)

    # def cargar_imagen(self, image_path, width):

    # #Carga y escala la imagen a un ancho específico.
    #     try:
    #         pixbuf = GdkPixbuf.Pixbuf.new_from_file(image_path)
    #         aspect_ratio = pixbuf.get_height() / pixbuf.get_width()  # Mantener proporción
    #         scaled_pixbuf = pixbuf.scale_simple(width, int(width * aspect_ratio), GdkPixbuf.InterpType.BILINEAR)
    #         self.imagen.set_from_pixbuf(scaled_pixbuf)
    #     except Exception as e:
    #         print(f"Error al cargar la imagen: {e}")

    # Evento para ajustar la imagen al ancho de la ventana
    def on_window_resize(self, widget, allocation):
        
        #Redimensiona la imagen al ancho de la ventana.
        
        window_width = allocation.width
        self.cargar_imagen("imagen.png", window_width)

    def leer_csv(self, nombreArchivo):
        
        #Lee una matriz desde un archivo CSV y la retorna como lista de listas.
        
        matriz = []
        try:
            with open(nombreArchivo, newline='') as archivo_csv:
                lector_csv = csv.reader(archivo_csv)
                for fila in lector_csv:
                    matriz.append(fila)  # Agregar cada fila como lista
        except FileNotFoundError:
            print(f"Error: El archivo {nombreArchivo} no se encontró.")
        except Exception as e:
            print(f"Error al leer el archivo: {e}")
        return matriz


    # def cargar_imagen(self, image_path):
    #     pixbuf = GdkPixbuf.Pixbuf.new_from_file(image_path)
    #     scaled_pixbuf = pixbuf.scale_simple(2000, 2000, GdkPixbuf.InterpType.BILINEAR)
    #     self.imagen.set_from_pixbuf(scaled_pixbuf)



    def crear_columnas(self, num_columnas):
        """
        Crea las columnas dinámicamente en el ColumnView.
        """
        for i in range(num_columnas):
            factory = Gtk.SignalListItemFactory()
            factory.connect("setup", self.on_list_item_setup)
            factory.connect("bind", self.on_list_item_bind, i)

            # La primera columna será estática y mostrará los nombres de las filas
            column_title = "Nombre de la Fila" if i == 0 else f"Columna {i}"
            column = Gtk.ColumnViewColumn(
                title=column_title,
                factory=factory,
            )
            column.set_resizable(True)
            column.set_expand(True)
            self.columnview.append_column(column)

    def on_list_item_setup(self, factory, list_item):
        """
        Configura cada celda del ColumnView.
        """
        label = Gtk.Inscription()
        list_item.set_child(label)

    def on_list_item_bind(self, factory, list_item, columna_index):
        """
        Asigna el valor correspondiente a cada celda.
        """
        row = list_item.get_item()
        list_item.get_child().set_text(str(row.data[columna_index]))
    
    def on_button_clicked(self, button):

        # Crear un MessageDialog
        dialog = Gtk.MessageDialog(
            transient_for=None,
            message_type=Gtk.MessageType.INFO,
            buttons=Gtk.ButtonsType.OK,
            text="Este es un mensaje con una imagen.",
        )
        dialog.set_transient_for(button.get_root())

        # Crear un contenedor para la imagen y el texto
        vbox = Gtk.Box(orientation=Gtk.Orientation.VERTICAL, spacing=10)

        # Crear y cargar la imagen
        try:
            pixbuf = GdkPixbuf.Pixbuf.new_from_file("archivo.png")
            scaled_pixbuf = pixbuf.scale_simple(200, 200, GdkPixbuf.InterpType.BILINEAR)
            image = Gtk.Image.new_from_pixbuf(scaled_pixbuf)
            vbox.append(image)
        except Exception as e:
            print(f"Error al cargar la imagen: {e}")

        # Agregar el contenedor al área personalizada del MessageDialog
        vbox.append(Gtk.Label(label="Texto debajo de la imagen."))
        dialog.set_focus_child(vbox)

        # Mostrar el MessageDialog
        dialog.present()
        dialog.run()
        dialog.destroy()






class Gtk4TestApp(Gtk.Application):
    def __init__(self):
        super().__init__(application_id=APPID)

    def do_activate(self):
        window = Gtk4TestTest(self)
        window.present()


def main():
    app = Gtk4TestApp()
    app.run()


if __name__ == '__main__':
    main()