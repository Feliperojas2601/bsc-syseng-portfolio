import React from "react";
import ReactDOM from "react-dom";
import "./estilos/modalHorario.scss";

const ModalEditarCreditos = (props) => {
   return ReactDOM.createPortal(
      <div className="contenedor-modal-horario">
         <div className="modal-horario">
            <h3 className="modal-horario-titulo">Nuevo número de créditos</h3>

            <form className="modal-horario-formulario">
               <div className="modal-horario-formulario-controles">
                  <h4 className="modal-horario-subtitulo">{props.nombre}</h4>
                  <input
                     type="text"
                     className="modal-horario-formulario-texto"
                     placeholder="Número de créditos"
                  />
                  <input
                     type="submit"
                     className="modal-horario-formulario-botones"
                     value="Cambiar créditos"
                     onClick={props.terminarCambiandoCreditos}
                  />
               </div>
            </form>
            <button
               className="modal-horario-formulario-botones"
               onClick={props.terminarCambiandoCreditos}
            >
               Cancelar
            </button>
         </div>
      </div>,
      document.getElementById("modal")
   );
};

export default ModalEditarCreditos;
